#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Hud.h"

#include <vector>

class Level
{
private:
	std::vector<GameObject*> gameObjects;
	sf::Clock clock;
	sf::Time timeElapsedLastFrame;

	Player* playerPtr;

	Hud* hud;

	//sf::View* gameCamera;

public:
	Level();
	~Level();

	void update();
	void render(sf::RenderWindow& gameWindow);
	
	//sf::View* getGameCamera() const;
};

#endif // !LEVEL_H