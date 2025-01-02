#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"

#include <vector>

class Game
{
private:
	static const int VWIDTH = 1366;
	static const int VHEIGHT = 768;

	sf::RenderWindow window;
	Level level;

	void eventHandler();
	void update();
	void render();

public:
	Game();
	~Game();
	void start();
};

#endif // !GAME_H
