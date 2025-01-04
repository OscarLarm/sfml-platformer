#include "Game.h"
#include <iostream>

void Game::eventHandler()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || 
			this->gameState == 5)
		{
			this->window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (this->gameState)
			{
			case 0:
				mainMenu.setMenuState(event);
				break;
			default:
				break;
			}
		}
	}
}

void Game::update()
{
	this->timeElapsedLastFrame = this->clock.restart();

	switch (this->gameState)
	{
	case 0:
		this->gameState = mainMenu.update();
		break;
	case 1:
		/*if (playerPtr->isHit())
		{
			this->level.load();
		}*/
		level.update(timeElapsedLastFrame);
		break;
	default:
		break;
	}
}

void Game::render()
{
	this->window.clear();

	switch (this->gameState)
	{
	case 0:
		window.draw(this->mainMenu);
		break;
	case 1:
		level.render(this->window);
		break;
	default:
		break;
	}

	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer"/*, sf::Style::Close*/),
	gameState(0),
	mainMenu(sf::Vector2i(VWIDTH, VHEIGHT), "Platformer", "Made in SFML", "- Press 'Enter to start\n\n\n\n- Press 'ESC' to quit"),
	playerPtr(level.getPlayer())
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
