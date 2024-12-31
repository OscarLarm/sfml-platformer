#include "Game.h"

void Game::eventHandler()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}
	}
}

void Game::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	/*this->player.update(timeElapsedLastFrame, platformVector);
	this->enemy.update(timeElapsedLastFrame, platformVector);*/


	for (auto* character : gameObjects)
	{
		Character* characterPtr = nullptr;

		characterPtr = dynamic_cast<Character*>(character);

		if (characterPtr != nullptr)
		{
			characterPtr->update(timeElapsedLastFrame, platformVector);
		}

	}

	/*for (auto* character : gameObjects)
	{
		Character* characterPtr = nullptr;

		characterPtr = dynamic_cast<Character*>(character);

		if (characterPtr != nullptr)
		{
			characterPtr->update(timeElapsedLastFrame, gameObjects);
		}

	}*/
}

void Game::render()
{
	this->window.clear();

	for (auto* object : gameObjects)
	{
		this->window.draw(*object);
	}

	/*this->window.draw(this->player);
	this->window.draw(this->enemy);
	for  (const Platform& i : platformVector)
	{
		this->window.draw(i);
	}*/

	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer"/*, sf::Style::Close*/)
{
	gameObjects.push_back(new Player);
	gameObjects.push_back(new Enemy);

	float count = 0.0f;
	float count2 = 0.0f;
	this->window.setVerticalSyncEnabled(true);
	for (int i = 0; i < 15; i++)
	{
		Platform* platform = new Platform;
		platform->setPosition(sf::Vector2f(0.0f + 16.0f * count++, 650.0f));
		gameObjects.push_back(platform);
		platformVector.push_back(platform);
	}
	for (int i = 16; i < 19; i++)
	{
		Platform* platform = new Platform;
		platform->setPosition(sf::Vector2f(0.0f + 16.0f * (count - 1.0f), 650.0f - 16.0f * ++count2));
		gameObjects.push_back(platform);
		platformVector.push_back(platform);

	}
	for (int i = 19; i < 75; i++)
	{
		Platform* platform = new Platform;
		platform->setPosition(sf::Vector2f(0.0f + 16.0f * count++, 650.0f));
		gameObjects.push_back(platform);
		platformVector.push_back(platform);

	}
}

Game::~Game()
{
}

void Game::start()
{
	while (this->window.isOpen())
	{
		eventHandler();
		update();
		render();
	}
}
