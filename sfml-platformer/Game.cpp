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
				//this->level->load(level01.data(), 40, 20, sf::Vector2i(16, 16));
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
		//if (playerPtr->isHit())
		//{
		//	level->reset();
		//}
		if (this->playerPtr == nullptr || !this->playerPtr->isAlive())
		{
			this->playing = false;
			this->menuChoice = 1;
		}
		else if (this->level->getWin())
		{
			this->playing = false;
			this->menuChoice = 2;
		}
		else
		{
			level->update(timeElapsedLastFrame);
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
		case 2:
			this->menu.updateMenuText(
				"Success", "Time: " + 
				std::to_string(static_cast<int>(this->level->getTimer())) +
				" seconds", "restart", "quit");
			break;
		default:
			break;
		}
		window.draw(this->menu);
	}
	else
	{
		level->render(this->window);

	}

	this->window.display();
}

Game::Game()
	:LEVEL_SIZE(sf::Vector2f(640.0f, 320.0f)),
	window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer"/*, sf::Style::Close*/),
	//mainMenu(sf::Vector2i(VWIDTH, VHEIGHT), "Platformer", "Made in SFML", "start", "quit"),
	//defeatMenu(sf::Vector2i(VWIDTH, VHEIGHT), "Defeat", "You have been slain", "restart", "return to the main menu"),
	playing(false),
	menu(sf::Vector2i(688.0f, 430.0f), "Platformer", "Made in SFML", "Start", "quit"),
	menuChoice(0),
	playerPtr(nullptr),
	gameView(sf::Vector2f(LEVEL_SIZE.x / -4, LEVEL_SIZE.y / -4), sf::Vector2f(800.0f,600.0f))/*,
	view(sf::Vector2f(320.0f, 160.0f), sf::Vector2f(688.0f, 430.0f))*/
{
	this->window.setVerticalSyncEnabled(true);
	this->level = new Level();
	this->playerPtr = level->getPlayer();

	this->view.reset(gameView);
	this->window.setView(view);
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
