#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
private:
	static const int VWIDTH = 1280;
	static const int VHEIGHT = 720;

	sf::Clock clock;
	sf::Time timeElapsedLastFrame;

	sf::RenderWindow window;

	void eventHandler();
	void update();
	void render();

	Player player;

public:
	Game();
	~Game();
	void start();
};

#endif // !GAME_H