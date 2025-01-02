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
	level.update();
}

void Game::render()
{
	this->window.clear();

	level.render(this->window);
	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer", sf::Style::Close)
{
	this->window.setVerticalSyncEnabled(true);
	//this->window.setView(*this->level.getGameCamera());
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
