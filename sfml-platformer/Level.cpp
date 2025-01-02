#include "Level.h"

Level::Level()
{
	// Temporary before adding tilemap
	playerPtr = new Player;
	gameObjects.push_back(playerPtr);
	gameObjects.push_back(new Enemy);
	gameObjects.push_back(playerPtr->getSword());
	hud = new Hud(playerPtr);

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
	//gameCamera = new sf::View(sf::FloatRect(50, 350, 640, 360));
}

Level::~Level()
{
}

void Level::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	this->hud->update(this->timeElapsedLastFrame);
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
	gameWindow.draw(*hud);
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

//sf::View* Level::getGameCamera() const
//{
//	return this->gameCamera;
//}
