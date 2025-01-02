#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

#include <vector>

class Game
{
private:
	static const int VWIDTH = 1366;
	static const int VHEIGHT = 768;

	sf::Clock clock;
	sf::Time timeElapsedLastFrame;

	sf::RenderWindow window;

	void eventHandler();
	void update();
	void render();

	/*Player player;
	Platform platform[75];
	Enemy enemy;*/

	std::vector<GameObject*> gameObjects;

public:
	Game();
	~Game();
	void start();
};

#endif // !GAME_H
