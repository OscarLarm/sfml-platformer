#include "Level.h"


Level::Level()
	: timer(0.0f),
	win(false),
	playerPtr(nullptr)
{
	this->load(level01.data(), 40, 20, sf::Vector2i(16, 16));
	//hud = new Hud(this->getPlayer()); // Move to Game class, different from UML diagram.
}

Level::~Level()
{
	gameObjects.clear();
	delete this->hud;
	hud = nullptr;
}

void Level::update(const sf::Time& timeElapsedLastFrame)
{
	this->timer += timeElapsedLastFrame.asSeconds();
	//this->hud->update(this->timer);

	for (auto* i : gameObjects)
	{
		if (i == nullptr)
		{
			continue;
		}

		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(i);

		if (characterPtr != nullptr)
		{
			characterPtr->update(timeElapsedLastFrame, gameObjects);
		}

		WinObject* winObjectPtr = nullptr;
		winObjectPtr = dynamic_cast<WinObject*>(i);

		if (winObjectPtr != nullptr)
		{
			this->win = winObjectPtr->update(timeElapsedLastFrame);
		}
	}
}

void Level::render(sf::RenderWindow& gameWindow)
{
	//for (auto& i : gameObjects)
	//{
	//	if (i != nullptr)
	//	{
	//		gameWindow.draw(*i);
	//	}
	//}

	//gameWindow.draw(*hud);
	//gameWindow.draw(tileMap);
	for (auto* object : gameObjects)
	{
		if (object == nullptr)
		{
			continue;
		}
		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(object);

		if (characterPtr == nullptr || 
			characterPtr != nullptr && 
			characterPtr->isAlive())
		{
			gameWindow.draw(*object);
		}
	}
}

void Level::load(int* level, const int column, const int row, const sf::Vector2i& gridSize)
{
	this->win = false;
	gameObjects.clear();

	this->gameObjects.resize(column * row);

	int levelIndex = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			GameObject* gameObjectPtr = nullptr;
			switch (level[levelIndex])
			{
			case 0:
				break;
			case 1:
				gameObjectPtr = new Platform;
				break;
			case 2:
				gameObjectPtr = new WinObject;
				break;
			case 3:
				gameObjectPtr = new Player;
				this->playerPtr = static_cast<Player*>(gameObjectPtr);
				break;
			case 4:
				gameObjectPtr = new Enemy;
			}
			
			if (gameObjectPtr != nullptr)
			{
				gameObjectPtr->setPosition(sf::Vector2f(j * gridSize.x, i * gridSize.x)); // Why do I need to use column for y and row for x?
				gameObjects.push_back(gameObjectPtr);
			}
			gameObjectPtr = nullptr;

			levelIndex++;
		}
	}



	/*reset();
	for (auto& i : gameObjects)
	{
		Player* playerPtr = dynamic_cast<Player*>(i);
		if (playerPtr != nullptr)
		{
			playerPtr->resetState();
		}
		else
		{
			WinObject* winObjectPtr = dynamic_cast<WinObject*>(i);
			if (winObjectPtr != nullptr)
			{
				winObjectPtr->setWin(false);
			}

		}
	}*/
	this->timer = 0.0f;
}

void Level::reset()
{
	for (auto& i : gameObjects)
	{
		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(i);

		if (characterPtr != nullptr)
		{
			characterPtr->resetPosition();
		}
		
		characterPtr = dynamic_cast<Enemy*>(i);
		if (characterPtr != nullptr)
		{
			characterPtr->resetLives();
		}
	}
}

Player* Level::getPlayer() const
{
	return this->playerPtr;
}

bool Level::getWin() const
{
	return this->win;
}

float Level::getTimer() const
{
	return this->timer;
}
