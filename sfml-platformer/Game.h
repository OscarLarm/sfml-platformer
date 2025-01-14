#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Menu.h"
#include "Hud.h"

#include <vector>
#include <string>
#include <iostream>

class Game
{
private:
	const sf::Vector2i WINDOW_SIZE = sf::Vector2i(1366, 768);
	const std::string LEVEL_01_FILE_PATH = "../levels/level01.txt";

	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time timeElapsedLastFrame;
	float totTime;

	Level* level;
	Player* playerPtr;
	Menu menu;
	Hud* gameHud;

	sf::View menuView;
	sf::View gameView;

	bool playing;

	enum MenuChoice
	{
		Main,
		Defeat,
		Victory,
		Quit
	};
	MenuChoice currentMenu;

	void eventHandler();
	void update();
	void render();

public:
	Game();
	virtual ~Game();
	void start();
};

#endif // !GAME_H
