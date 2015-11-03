//File UnitHandling

#include "UnitHandling.h"

UnitHandling::UnitHandling(sf::RenderWindow & window) :
	window{ window }
{}

bool UnitHandling::checkSpaceFree(sf::Vector2f pos) {
	for (auto const & t : *terrainContainer) {
		if ((t->checkClicked(pos)) && (!(t->getFree()))) {			// checken of dit terrain vakje wel vrij is
			return false;
		}
	}
	return true;
}

bool UnitHandling::checkWalk(sf::Vector2f pos) {
	if (checkSpaceFree(pos)) {
		for (auto const & t : *terrainContainer) {
			if (t->checkClicked(pos)) {
				if ((t->getColor() == sf::Color::Blue) || (t->getColor() == sf::Color::Red) || (t->getColor() == sf::Color::Green)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool UnitHandling::checkAttack(sf::Vector2f pos) {
	for (auto const & t : *terrainContainer) {
		if (t->checkClicked(pos)) {
			if ((t->getColor() == sf::Color::Blue) || (t->getColor() == sf::Color::Red) || (t->getColor() == sf::Color::Magenta)) {
				return true;
			}
		}
	}
	return false;
}

void UnitHandling::unitControl(sf::Vector2f mPosition, std::vector<std::unique_ptr<Unit>> * currentPlayerUnits, std::vector<std::unique_ptr<Unit>> * enemyPlayerUnits, std::vector<std::unique_ptr<Building>> * enemyPlayerBuildings, sf::Color color) {			// het afhandelen van de movement, aanvallen en actions van de units
	if (!unitSelected) {
		markField(unitWalklimit, unitAttackrange, true, unitPosition, sf::Color::White);
		for (auto const & p : *currentPlayerUnits) {
			if (p->checkClicked(mPosition)) {
				unitSelected = true;
				allySelected = true;
				p->makeSelected(mPosition);

				auto ip = std::find(currentPlayerUnits->begin(), currentPlayerUnits->end(), p);
				if (ip != currentPlayerUnits->end()) {
					unitIndex = std::distance(currentPlayerUnits->begin(), ip);
				}

				unitPosition = p->getTilePosition();		// onthouden voor het deselecteren van de tiles
				unitWalklimit = p->getWalklimit();
				unitAttackrange = p->getAttackrange();
				markField(unitWalklimit, unitAttackrange, false, unitPosition, color);
				break;
			}
		}
		for (auto const & p : *enemyPlayerUnits) {
			if (p->checkClicked(mPosition)) {
				unitSelected = true;
				allySelected = false;

				auto ip = std::find(enemyPlayerUnits->begin(), enemyPlayerUnits->end(), p);
				if (ip != enemyPlayerUnits->end()) {
					enemyIndex = std::distance(enemyPlayerUnits->begin(), ip);
				}
				break;
			}
		}
	}
	else if (unitSelected && allySelected) {
		// lopen:
		if (checkWalk(mPosition)) {
			for (auto const & t : *terrainContainer) {
				if (t->checkClicked(currentPlayerUnits->at(unitIndex)->getTilePosition())) {
					t->setFree(true);								// terrain weer vrijgeven
				}
			}
			currentPlayerUnits->at(unitIndex)->walk(mPosition);		// lopen
			for (auto const & t : *terrainContainer) {
				if (t->checkClicked(mPosition)) {
					if (currentPlayerUnits->at(unitIndex)->getWalklimit() == 1) {
						(playerB.getActive()) ? playerB.diffUnitWalks(-1) : playerR.diffUnitWalks(-1);
					}
					t->setFree(false);								// terrain bezetten
				}
			}
		}
		// aanvallen enemyUnits:
		int i = 0;
		if (currentPlayerUnits->at(unitIndex)->getAttackrange() > 0) {
			for (auto const & q : *enemyPlayerUnits) {
				i++;
				if (q->checkClicked(mPosition)) {		// check of vijand wordt aangeklikt en dus of er een aanval moet komen
					if (checkAttack(mPosition)) {
						(playerB.getActive()) ? playerB.diffUnitAttacks(-1) : playerR.diffUnitAttacks(-1);
						if (q->damage(currentPlayerUnits->at(unitIndex)->attack())) {		// hij krijgt true mee als hij geen hp meer heeft, dus dan moet je hem verwijderen uit de container
							for (auto const & t : *terrainContainer) {
								if (t->checkClicked(q->getTilePosition())) {
									t->setFree(true);										// terrain weer vrij maken
								}
							}
							enemyPlayerUnits->erase(enemyPlayerUnits->begin() + i - 1);
						}
					}
					break;
				}
			}
			// aanvallen Buildings:
			i = 0;
			for (auto const & q : *enemyPlayerBuildings) {
				i++;
				if (q->checkClicked(mPosition)) {
					if (checkAttack(mPosition)) {
						if (q->damage(currentPlayerUnits->at(unitIndex)->attack())) {
							for (auto const & t : *terrainContainer) {
								if (t->checkClicked(q->getTilePosition())) {
									t->setFree(true);
								}
							}
							q->checkAction(cQueue);
							enemyPlayerBuildings->erase(enemyPlayerBuildings->begin() + i - 1);
						}
						(playerB.getActive()) ? playerB.diffUnitAttacks(-1) : playerR.diffUnitAttacks(-1);
					}
					break;
				}
			}

			// resources verkrijgen:
			for (auto const & r : resourceContainer) {
				if (r->checkClicked(V2f_from_V2i(sf::Mouse::getPosition(window)))) {		// check of vijand wordt aangeklikt en dus of er een aanval moet komen
					if (checkAttack(mPosition) && checkResource(mPosition, currentPlayerUnits->at(unitIndex)->getTilePosition())) {			// checken of unit naast resource staat
						(playerB.getActive()) ? playerB.diffUnitAttacks(-1) : playerR.diffUnitAttacks(-1);
						(playerB.getActive()) ? playerB.setMoney(playerB.getMoney() + r->getMoney()) : playerR.setMoney(playerR.getMoney() + r->getMoney());
						currentPlayerUnits->at(unitIndex)->resource();
					}
					break;
				}
			}
		}
		currentPlayerUnits->at(unitIndex)->setSelected(false);
		unitSelected = false;
		allySelected = false;
		unitIndex = 0;												// errorverhelpend anders raakt de HUD in de stress. info JP
		std::cout << "deselected unit\n";

		markField(unitWalklimit, unitAttackrange, true, unitPosition, sf::Color::White);
	}
	else {
		unitSelected = false;
		allySelected = false;
	}
}