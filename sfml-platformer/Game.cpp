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
}

void Game::render()
{
	window.clear(sf::Color::Black);

	//window.draw();

	window.display();
}

Game::Game()
	: window(sf::VideoMode(900, 600), "Platformer")
{
}

Game::~Game()
{
}

void Game::start()
{
	while (this->window.isOpen())
	{
		this->eventHandler();
		this->update();
		this->render();
	}
}
