#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "WinObject.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <fstream>

class Level
{
private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	Player* playerPtr;
	
	bool win;

	std::array<int, 3200> levelArray;
	// 	std::unique_ptr<int[]>levelArray;


	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;


public:
	Level();
	virtual ~Level();

	void update(const sf::Time& timeElapsedLastFrame);
	void render(sf::RenderWindow& gameWindow);
	void load(const std::string& levelDataPath, const int column, const int row, const sf::Vector2i& gridSize);
	void reset();

	Player* getPlayer() const;
	bool getWin() const;
	void setBackgroundPosition(const sf::View& gameView);
};

#endif // !LEVEL_H
