#include "Level.h"
#include <iostream>

Level::Level()
	: timer(0.0f)
{
	// Temporary before adding tilemap
	gameObjects.push_back(new Player);
	gameObjects.push_back(new Enemy);
	gameObjects.push_back(this->getPlayer()->getSword());

	float count = 0.0f;
	float count2 = 0.0f;

	// Temporary before adding tilemap
	for (int i = 0; i < 15; i++)
	{
		Platform* platform = new Platform;
		platform->setPosition(sf::Vector2f(0.0f + 16.0f * count++, 650.0f));
		gameObjects.push_back(platform);
	}
	for (int i = 16; i < 19; i++)
	{
		Platform* platform = new Platform;
		platform->setPosition(sf::Vector2f(0.0f + 16.0f * (count - 1.0f), 650.0f - 16.0f * ++count2));
		gameObjects.push_back(platform);
	}
	for (int i = 19; i < 75; i++)
	{
		Platform* platform = new Platform;
		platform->setPosition(sf::Vector2f(0.0f + 16.0f * count++, 650.0f));
		gameObjects.push_back(platform);
	}

	//this->load();
	hud = new Hud(this->getPlayer());
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
	this->hud->update(this->timer);

	for (auto* character : gameObjects)
	{
		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(character);

		if (characterPtr != nullptr)
		{
			characterPtr->update(timeElapsedLastFrame, gameObjects);
		}
	}
}

void Level::render(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(*hud);

	for (auto* object : gameObjects)
	{
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

void Level::load()
{
	//for (auto& i : gameObjects)
	//{
	//	delete i;
	//	i = nullptr;
	//}
	reset();
	for (auto& i : gameObjects)
	{
		Player* playerPtr = dynamic_cast<Player*>(i);
		if (playerPtr != nullptr)
		{
			playerPtr->resetState();
		}
	}
	this->timer = 0.0f;

	//gameCamera = new sf::View(sf::FloatRect(50, 350, 640, 360));
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
	Player* playerPtr = nullptr;
	for (auto& i : gameObjects)
	{
		Player* playerPtr = dynamic_cast<Player*>(i);

		if (playerPtr != nullptr)
		{
			return playerPtr;
		}
	}
	return playerPtr;
}

//sf::View* Level::getGameCamera() const
//{
//	return this->gameCamera;
//}
