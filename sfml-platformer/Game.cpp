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

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			this->player.jump(this->timeElapsedLastFrame);
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
	//for (int i = 0; i < 20; i++)
	//{
	//	window.draw(*this->platform[i]);
	//}
	//window.draw(*this->platform);

	window.display();
}

void Game::collision()
{
	//if (player.getSprite().getGlobalBounds().intersects(this->platform->getSprite().getGlobalBounds()))
	//{
	//	std::cout << "collision!" << std::endl;
	//}


	//// Stops at player collision with window border
	//if (this->player.getSprite().getGlobalBounds().left <= 0.0f)
	//{
	//	this->player.setPosition(sf::Vector2f(0.0f, this->player.getPosition().y));
	//}
	//else if (
	//	this->player.getSprite().getGlobalBounds().left + 
	//	this->player.getSprite().getGlobalBounds().width >= 
	//	window.getSize().x)
	//{
	//	this->player.setPosition(sf::Vector2f(
	//		this->window.getSize().x - this->player.getSprite().getGlobalBounds().width, 
	//		this->player.getPosition().y));
	//}
	
	//if (this->player.getSprite().getGlobalBounds().top <= 0.0f)
	//{
	//	this->player.setPosition(sf::Vector2f(this->player.getPosition().x, 0.0f));
	//}
	//else if (
	//	this->player.getSprite().getGlobalBounds().top +
	//	this->player.getSprite().getGlobalBounds().height >=
	//	window.getSize().y)
	//{
	//	this->player.setPosition(sf::Vector2f(
	//		this->player.getPosition().x,
	//		this->window.getSize().y - this->player.getSprite().getGlobalBounds().height));
	//}
	
	
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer", sf::Style::Close)
{
	this->window.setVerticalSyncEnabled(true);
	//this->platform = new Platform(sf::Vector2f(31.0f, 696.0f));
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
