#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Hud.h"
#include "WinObject.h"
//#include "TileMap.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <fstream>

class Level
{
private:
	std::vector<GameObject*> gameObjects;

	Player* playerPtr;
	float timer;
	
	bool win;

	std::array<int, 3200> level01;
	//TileMap tileMap;


public:

	Level();
	virtual ~Level();

	void update(const sf::Time& timeElapsedLastFrame);
	void render(sf::RenderWindow& gameWindow);
	void load(/*int* level,*/ const int column, const int row, const sf::Vector2i& gridSize);
	void reset();

	Player* getPlayer() const;
	bool getWin() const;
	float getTimer() const;

};

#endif // !LEVEL_H
