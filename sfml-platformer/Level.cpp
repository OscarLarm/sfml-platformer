#include "Level.h"

Level::Level()
{
	// Temporary before adding tilemap
	gameObjects.push_back(new Player);
	gameObjects.push_back(new Enemy);

	for (auto* i : gameObjects)
	{
		GameObject* playerPtr = nullptr;

		Player* player = dynamic_cast<Player*>(i);
		if (playerPtr != nullptr)
		{
			gameObjects.push_back(player->getSword());
		}
	}
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
}

Level::~Level()
{
}

void Level::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	int counter = 0;

	for (auto* character : gameObjects)
	{
		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(character);

		if (characterPtr != nullptr)
		{
			characterPtr->update(timeElapsedLastFrame, gameObjects);

			if (!characterPtr->isAlive())
			{
				gameObjects.erase(gameObjects.begin() + counter);
			}
		}
		counter++;
	}
}

void Level::render(sf::RenderWindow& gameWindow)
{
	for (auto* object : gameObjects)
	{
		gameWindow.draw(*object);

		Player* playerPtr = nullptr;
		playerPtr = dynamic_cast<Player*>(object);

		if (playerPtr != nullptr)
		{
			gameWindow.draw(*playerPtr->getSword());
		}
	}
}
