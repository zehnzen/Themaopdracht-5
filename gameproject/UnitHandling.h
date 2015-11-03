//File UnitHandling.h

#ifndef _UNITHANDLING_H
#define _UNITHANDLING_H

#include "Building.h"
#include "Unit.h"
#include "Terrain.h"

class UnitHandling {
public:
	UnitHandling(sf::RenderWindow & window) {};

	void setTerrainVector(std::vector<std::unique_ptr<Terrain>>* terrains);

	void unitControl(sf::Vector2f, std::vector<std::unique_ptr<Unit>> * cPUnits, std::vector<std::unique_ptr<Unit>> * ePUnits, std::vector<std::unique_ptr<Building>> * ePBuildings, sf::Color color);		// afhandeling van de acties van de units
	bool checkSpaceFree(sf::Vector2f pos);
	bool checkWalk(sf::Vector2f pos);
	bool checkAttack(sf::Vector2f pos);

	void setUnitSelected(bool);
	void setAllySelected(bool);
	bool getUnitSelected();
	bool getAllySelected();
	int getUnitIndex();
	int getEnemyIndex();
	std::unique_ptr<Unit>* getUnitPointer();


private:
	std::vector<std::unique_ptr<Terrain>>* terrainContainer;
	sf::RenderWindow & window;

	bool unitSelected = false;
	bool allySelected = false;
	int unitIndex;
	int enemyIndex;
};

#endif