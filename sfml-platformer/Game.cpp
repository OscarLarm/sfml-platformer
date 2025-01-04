#include "Game.h"
#include <iostream>

void Game::eventHandler()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			this->menuChoice == -1)
		{
			this->window.close();
		}

		if (!playing && event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				this->level.load();
				this->playing = true;
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				this->menuChoice = -1;
			} 
		}
	}
}

void Game::update()
{
	this->timeElapsedLastFrame = this->clock.restart();
	if (playing)
	{
		if (playerPtr->isHit())
		{
			level.reset();
		}
		if (!this->playerPtr->isAlive())
		{
			this->playing = false;
			this->menuChoice = 1;
		}
		else
		{
			level.update(timeElapsedLastFrame);
		}
	}
}

void Game::render()
{
	this->window.clear();

	if (!playing)
	{
		switch (menuChoice)
		{
		case 0:
			this->menu.updateMenuText("Platformer", "Made in SFML", "start", "quit");
			break;
		case 1:
			this->menu.updateMenuText("Defeat", "You have been slain", "restart", "quit");
			break;
		default:
			break;
		}
		window.draw(this->menu);
	}
	else
	{
		level.render(this->window);
	}

	this->window.display();
}

Game::Game()
	: window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer"/*, sf::Style::Close*/),
	//mainMenu(sf::Vector2i(VWIDTH, VHEIGHT), "Platformer", "Made in SFML", "start", "quit"),
	//defeatMenu(sf::Vector2i(VWIDTH, VHEIGHT), "Defeat", "You have been slain", "restart", "return to the main menu"),
	playerPtr(level.getPlayer()),
	playing(false),
	menu(sf::Vector2i(VWIDTH, VHEIGHT), "Platformer", "Made in SFML", "Start", "quit"),
	menuChoice(0)
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
