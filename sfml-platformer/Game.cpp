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

		//// FOR DEBUGGING
		//if (event.type == sf::Event::KeyReleased)
		//{
		//	std::cout << this->player.getPosition().x << ", " << this->player.getPosition().y << std::endl;
		//}
	}
}

void Game::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	//std::cout << "Frames: " << 1.0f / this->timeElapsedLastFrame.asSeconds() << std::endl;

	this->collision();
	this->player.controller(timeElapsedLastFrame);
}

void Game::render()
{
	window.clear();
	window.draw(this->player);
	for (int i = 0; i < 20; i++)
	{
		window.draw(*this->platform[i]);
	}

	window.display();
}

void Game::collision()
{
	for (const auto& i : platform)
	{
		if (player.getSprite().getGlobalBounds().intersects(i->getSprite().getGlobalBounds()))
		{
			std::cout << "collision!" << std::endl;
		}
	}
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer", sf::Style::Close)
{
	this->window.setVerticalSyncEnabled(true);

	for (int i = 0; i < 15; i++)
	{
		this->platform[i] = new Platform(sf::Vector2f(31.0f * i, 696.0f));
	}
	for (int i = 15; i < 19; i++)
	{
		this->platform[i] = new Platform(sf::Vector2f(155.0f, 696.0f - (31.0f *(i-15))));
	}
	this->platform[19] = new Platform(sf::Vector2f(155.0f, 510.0f));
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
