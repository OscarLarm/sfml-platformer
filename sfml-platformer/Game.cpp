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
	this->player.update(timeElapsedLastFrame, platformVector);
	this->enemy.update(timeElapsedLastFrame, platformVector);

}

void Game::render()
{
	this->window.clear();

	this->window.draw(this->player);
	this->window.draw(this->enemy);
	for  (const Platform& i : platformVector)
	{
		this->window.draw(i);
	}

	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer"/*, sf::Style::Close*/)
{
	float count = 0.0f;
	float count2 = 0.0f;
	this->window.setVerticalSyncEnabled(true);
	for (int i = 0; i < 15; i++)
	{
		platform[i].setPosition(sf::Vector2f(0.0f + 16.0f * count++, 650.0f));
		platformVector.push_back(platform[i]);
	}
	for (int i = 16; i < 19; i++)
	{
		platform[i].setPosition(sf::Vector2f(0.0f + 16.0f * (count -1.0f), 650.0f - 16.0f * ++count2));
		platformVector.push_back(platform[i]);
	}
	for (int i = 19; i < 75; i++)
	{
		platform[i].setPosition(sf::Vector2f(0.0f + 16.0f * count++, 650.0f));
		platformVector.push_back(platform[i]);
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
