#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Hud.h"
#include "WinObject.h"
#include "TileMap.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>

class Level
{
private:
	std::vector<GameObject*> gameObjects;

	Player* playerPtr;
	float timer;

	Hud* hud;
	
	bool win;

	std::array<int, 1980> level01 = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	TileMap tileMap;


public:

	Level();
	~Level();

	void update(const sf::Time& timeElapsedLastFrame);
	void render(sf::RenderWindow& gameWindow);
	void load(const int* level);
	void reset();

	Player* getPlayer() const;
	bool getWin() const;
	float getTimer() const;

};

#endif // !LEVEL_H
