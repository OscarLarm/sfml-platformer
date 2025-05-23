#include "Game.h"

void Game::eventHandler()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			this->currentMenu == Quit)
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
				this->currentMenu = Quit;
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
		this->gameHud->update(this->totTime, this->playerPtr->getLives(), this->gameView);
		this->level->setBackgroundPosition(this->gameView);

		if (this->playerPtr->isHit())
		{
			this->level->reset();
		}
		if (!this->playerPtr->isAlive())
		{
			this->playing = false;
			this->currentMenu = Defeat;
		}
		else if (this->level->getWin())
		{
			this->playing = false;
			this->currentMenu = Victory;
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
		switch (currentMenu)
		{
		case Main:
			this->menu.updateMenuText(
				"Platformer", 
				"Made in SFML", 
				"start", "quit");
			break;
		case Defeat:
			this->menu.updateMenuText(
				"Defeat", 
				"You have been slain", 
				"restart", "quit");
			break;
		case Victory:
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
	:window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Platformer", sf::Style::Close),
	totTime(0.0f),
	playing(false),
	menu(WINDOW_SIZE),
	currentMenu(Main),
	playerPtr(nullptr),
	menuView(sf::FloatRect(0.0f, 0.0f, WINDOW_SIZE.x, WINDOW_SIZE.y)),
	gameView(sf::FloatRect(0.0f, 0.0f, WINDOW_SIZE.x / 1.75, WINDOW_SIZE.y / 1.75))
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
