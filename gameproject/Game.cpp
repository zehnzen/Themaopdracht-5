//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"
#include "Soldier.h"

Game::Game() :
	window(sf::VideoMode(640, 480), "SFML window"),
	playerB{ sf::Color::Blue, true},
	playerR{ sf::Color::Red, false}
	{
		loadTextures();
		loadMenu();
		initText();
		makePlayfield();
		music.play(musicID::MENUTHEME);
		music.setVolume(7);
}

void Game::initText() {
	font.loadFromFile("arial.ttf");
	// Create a text
	text.setString("standaardtekst, graag vervangen");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
}
struct buttonVal {
	textureID id;
	sf::Vector2f pos;
	sf::Vector2f movingDirection;
};
void Game::loadMenu()
{
	inMenu = true;
	//de val1, 2 en 3 worden buiten scherm getekend(800, 100, 1200) en komen dan naar binnen bewegen
	buttonVal val1{ textureID::BACKGROUND };
	buttonVal val2{ textureID::START,		sf::Vector2f(800,260),	sf::Vector2f(1,0) };
	buttonVal val3{ textureID::OPTION,		sf::Vector2f(1000,330),	sf::Vector2f(1,0) };
	buttonVal val4{ textureID::EXIT,		sf::Vector2f(1200,400),	sf::Vector2f(1,0) };
	buttonVal val5{ textureID::MUTE,		sf::Vector2f(50,1000),	sf::Vector2f(1,0) };
	buttonVal val6{ textureID::BACK,		sf::Vector2f(50,1000),	sf::Vector2f(1,0) };

	std::array<buttonVal, 6> menus{ val1, val2, val3, val4, val5, val6 };

	for (buttonVal value : menus) {
		std::unique_ptr<MenuButton> menubutton(new MenuButton(value.id, textures, value.pos, value.movingDirection));
		menuContainer.push_back(std::move(menubutton));
	}
}

void Game::loadTextures() {
	textures.load(textureID::GRASS, "grass.jpg");
	textures.load(textureID::ROAD, "road.jpg");
	textures.load(textureID::UNIT, "unit.jpg");
	textures.load(textureID::BACKGROUND, "images//background.jpe");
	textures.load(textureID::START, "images//start.png");
	textures.load(textureID::OPTION, "images//option.png");
	textures.load(textureID::EXIT, "images//exit.png");
	textures.load(textureID::MUTE, "images//muteSound.png");
	textures.load(textureID::BACK, "images//back.png");
}

void Game::makePlayfield() {
	const int playfieldX = 10;
	const int playfieldY = 8;

	for (float y = 0; y < playfieldY; y++) {
		for (float x = 0; x < playfieldX; x++) {
			if (x == 3 || x == 6) {
				std::unique_ptr<Terrain> terrain(new Terrain(textureID::ROAD, textures, sf::Vector2f{ x * TILESIZE, y * TILESIZE }));
				terrainContainer.push_back(std::move(terrain));
			}
			else {
				std::unique_ptr<Terrain> terrain(new Terrain(textureID::GRASS, textures, sf::Vector2f{x * TILESIZE, y * TILESIZE}));
				terrainContainer.push_back(std::move(terrain));
			}
		}
	}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Game::handleInput(sf::Keyboard::Key key, bool b) {
	//Deze commands alleen bij indrukken
	if (b) {
		if (key == sf::Keyboard::W) {
			sf::Vector2i pos = (sf::Mouse::getPosition(window));
			std::unique_ptr<Unit> unit(new Unit(textureID::UNIT, textures, V2f_from_V2i(v2i_MOD(pos, TILESIZE)), getActivePlayer().getPlayer()));
			if (playerB.getActive()) { unitBContainer.push_back(std::move(unit)); }
			else { unitRContainer.push_back(std::move(unit)); }
		}
		else if (key == sf::Keyboard::S) {
			switchPlayer();
		}
		else if (key == sf::Keyboard::P) {
			inMenu = true;
			music.setVolume(10);
		}
	}
}

void Game::handleMouse(sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		// hier wat er moet gebeuren bij linker muisklik:
		// - check position van muis

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if(inMenu)
			{
				for (auto const & p : menuContainer) {
					if (p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)), window, menuContainer, music) == 1) {//TODO test voor start
						inMenu = false;
					}
				}
			}
			if (playerB.getActive()) {
				markField(oldUnitWalklimit, oldUnitPosition, sf::Color::White);
				for (auto const & p : unitBContainer) {							
					p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)));
					if (p->getSelected()) {
						oldUnitPosition = p->getPosition();		// onthouden voor het deselecteren van de tiles
						oldUnitWalklimit = p->getWalklimit();
						markField(p->getWalklimit(), p->getPosition(), sf::Color::Blue);
					}
				}
			}
			else {
				markField(oldUnitWalklimit, oldUnitPosition, sf::Color::White);
				for (auto const & p : unitRContainer) {							
					p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)));
					if (p->getSelected()) {
						oldUnitPosition = p->getPosition();		// onthouden voor het deselecteren van de tiles
						oldUnitWalklimit = p->getWalklimit();
						markField(p->getWalklimit(), p->getPosition(), sf::Color::Blue);
					}
				}
			}
			
		}
	}
	//doet momenteel de switchplayer voor rechtermuisklik
	if (button == sf::Mouse::Right) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			switchPlayer();
		}
	}
}

Player Game::getActivePlayer() {
	if (playerB.getActive()) {
		return playerB;
	}
	else { return playerR; }
}

void Game::switchPlayer() {
	playerB.setActive(!playerB.getActive());
	for (auto const & p : unitBContainer) {						// alle units van B deselecteren
		p->setSelected(false);
	}
	playerR.setActive(!playerR.getActive());
	for (auto const & p : unitRContainer) {						// alle units van R deselecteren
		p->setSelected(false);
	}
}

void Game::markField(int walklimit, sf::Vector2f position, sf::Color color) {									// mark the field (1 terrain) in order to show a units walking limit
	for (auto const & t : terrainContainer) {
		for (int i = 0; i <= walklimit; i ++) {
			if ((t->getPosition().x == ((position.x - 7) - (TILESIZE * i))) && (t->getPosition().y == (position.y - 7))) {		// rechts
				t->changeColor(color);
			}
			if ((t->getPosition().x == ((position.x - 7) + (TILESIZE * i))) && (t->getPosition().y == (position.y - 7))) {		// links
				t->changeColor(color);
			}
			if ((t->getPosition().y == ((position.y - 7) - (TILESIZE * i))) && (t->getPosition().x == (position.x - 7))) {		// boven
				t->changeColor(color);
			}
			if ((t->getPosition().y == ((position.y - 7) + (TILESIZE * i))) && (t->getPosition().x == (position.x - 7))) {		// onder
				t->changeColor(color);
			}
		}
	}
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handleInput(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				handleMouse(event.mouseButton.button);
				break;
			case sf::Event::LostFocus:
				inMenu = true;
				break;
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

void Game::update() {
	//TODO implement Command message structure which will be iterated here and each command delivered to it's target where it'll handle it's implementation
	//TODO the game updates
	
}

void Game::HUD() {
	text.setColor(getActivePlayer().getPlayer());
	text.setString("Money: " + std::to_string(getActivePlayer().getMoney()));
	text.setPosition(510, 0);
	window.draw(text);
	text.setString("Health: " + std::to_string(getActivePlayer().getPoints()));
	text.setPosition(510, 40);
	// Draw it
	window.draw(text);
}

void Game::render() {
	window.clear();
	if (inMenu) {
		for (const auto & p : menuContainer) {
			p->draw(window);		
			if( !(p->getPosition().x <= 50) ) {
				p->update(-1);
			}
			if(p->LoadedInScreen && p->getPosition().y <= 800) { //gekozen voor 800 zodat ik zeker weet dat hij buiten scherm ligt
				p->update(1);
			}
		}
	}	
	else {
		for (const auto & p : terrainContainer) {
			p->draw(window);
		}
		for (const auto & p : unitBContainer) {
			p->draw(window);
		}
		for (const auto & p : unitRContainer) {
			p->draw(window);
		}

		HUD();
	}
	window.display();
}