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

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			this->player.jump(this->timeElapsedLastFrame);
		}
	}
}

void Game::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	this->player.controller(timeElapsedLastFrame);
}

void Game::render()
{
	this->window.clear();

	this->window.draw(this->player);

	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer", sf::Style::Close),
	platform(nullptr)
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
