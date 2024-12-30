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
	this->player.controller(timeElapsedLastFrame, platformVector);
}

void Game::render()
{
	this->window.clear();

	this->window.draw(this->player);
	for  (const Platform& i : platformVector)
	{
		this->window.draw(i);
	}

	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer"/*, sf::Style::Close*/)
{
	int count = 0;
	int count2 = 0;
	this->window.setVerticalSyncEnabled(true);
	for (int i = 0; i < 15; i++)
	{
		platform[i].setPosition(sf::Vector2f(0 + 16 * count++, 650));
		platformVector.push_back(platform[i]);
	}
	for (int i = 16; i < 19; i++)
	{
		platform[i].setPosition(sf::Vector2f(0 + 16 * (count -1), 650 - 16 * ++count2));
		platformVector.push_back(platform[i]);
	}
	for (int i = 19; i < 30; i++)
	{
		platform[i].setPosition(sf::Vector2f(0 + 16 * count++, 650));
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
