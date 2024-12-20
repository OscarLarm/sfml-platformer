#include "Game.h"
#include <iostream> // FOR DEBUGGING

void Game::eventHandler()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}

		// FOR DEBUGGING
		if (event.type == sf::Event::KeyReleased)
		{
			std::cout << this->player.getPosition().x << ", " << this->player.getPosition().y << std::endl;
		}
	}
}

void Game::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	std::cout << "Frames: " << 1.0f / this->timeElapsedLastFrame.asSeconds() << std::endl;
	
	this->player.controller(timeElapsedLastFrame);
}

void Game::render()
{
	window.clear();
	window.draw(this->player);
	
	window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer", sf::Style::Close)
{
	this->window.setVerticalSyncEnabled(true);
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
