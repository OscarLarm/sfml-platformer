#include "Game.h"

Game::Game(int windowWidth, int windowHeight)
	: windowWidth(windowWidth), windowHeight(windowHeight)
{
}

Game::~Game()
{
}

void Game::start()
{
	this->window.create(sf::VideoMode(this->windowWidth, this->windowHeight), "Platformer", sf::Style::Close);

	while (this->window.isOpen())
	{
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed():
				this->end();

			default:
				break;
			}
		}
	}
}

void Game::end()
{
	this->window.close();
}
