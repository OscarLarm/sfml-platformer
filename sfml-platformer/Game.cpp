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
				this->totTime = 0.0f;
				this->level->load(this->LEVEL_01_FILE_PATH, 80, 40, sf::Vector2i(32, 16));
				this->playerPtr = level->getPlayer();
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
		if (playerPtr == nullptr)
		{
			return;
		}

		this->totTime += timeElapsedLastFrame.asSeconds();
		this->gameView.setCenter(playerPtr->getPosition().x, playerPtr->getPosition().y);
		this->gameHud->update(this->totTime, this->playerPtr, this->gameView);
		this->level->setBackgroundPosition(this->gameView);

		if (this->playerPtr->isHit())
		{
			this->level->reset();
		}
		if (!this->playerPtr->isAlive())
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
		window.setView(menuView);
		switch (menuChoice)
		{
		case 0:
			this->menu.updateMenuText(
				"Platformer", 
				"Made in SFML", 
				"start", "quit");
			break;
		case 1:
			this->menu.updateMenuText(
				"Defeat", 
				"You have been slain", 
				"restart", "quit");
			break;
		case 2:
			this->menu.updateMenuText(
				"Success", 
				"Time: " + std::to_string(static_cast<int>(totTime)) + " seconds", 
				"restart", "quit");
			break;
		default:
			break;
		}
		window.draw(this->menu);
	}
	else
	{
		window.setView(gameView);

		level->render(window);

		window.draw(*this->gameHud);
	}

	this->window.display();
}

Game::Game()
	:window(sf::VideoMode(VWIDTH, VHEIGHT), "Platformer", sf::Style::Close),
	totTime(0.0f),
	playing(false),
	menu(sf::Vector2i(VWIDTH, VHEIGHT)),
	menuChoice(0),
	playerPtr(nullptr),
	menuView(sf::FloatRect(0.0f, 0.0f, VWIDTH, VHEIGHT)),
	gameView(sf::FloatRect(0.0f, 0.0f, VWIDTH / 1.75, VHEIGHT / 1.75))
{
	this->window.setVerticalSyncEnabled(true); 
	this->level = new Level();
	this->gameHud = new Hud();
}

Game::~Game()
{
	delete level;
	delete gameHud;
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
