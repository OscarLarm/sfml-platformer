#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

#include <vector>

class Level
{
private:
	std::vector<GameObject*> gameObjects;
	sf::Clock clock;
	sf::Time timeElapsedLastFrame;

public:
	Level();
	~Level();

	void update();
	void render();
};

#endif // !LEVEL_H
