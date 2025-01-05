#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Menu.h"

#include <vector>
#include <string>

class Game
{
private:
	static const int VWIDTH = 1366;
	static const int VHEIGHT = 768;

	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time timeElapsedLastFrame;

	Level level;
	Player* playerPtr;
	Menu menu;

	bool playing;

	int menuChoice;

	void eventHandler();
	void update();
	void render();

	std::array<int, 50> level01 = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

public:
	Game();
	~Game();
	void start();
};

#endif // !GAME_H
