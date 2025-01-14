#include "Level.h"


Level::Level()
	: win(false),
	playerPtr(nullptr),
	levelArray({0})
{
	this->backgroundTexture.loadFromFile("../assets/background.png");
	this->backgroundSprite.setTexture(backgroundTexture);
	this->backgroundSprite.setOrigin(this->backgroundSprite.getGlobalBounds().width / 2, this->backgroundSprite.getGlobalBounds().height / 2);
}

Level::~Level()
{
	for (auto& i : gameObjects)
	{
		delete i;
	}
	gameObjects.clear();
}

void Level::update(const sf::Time& timeElapsedLastFrame)
{
	for (auto* i : gameObjects)
	{
		if (i == nullptr)
		{
			continue;
		}

		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(i);

		if (characterPtr != nullptr)
		{
			characterPtr->update(timeElapsedLastFrame, gameObjects);
		}

		WinObject* winObjectPtr = nullptr;
		winObjectPtr = dynamic_cast<WinObject*>(i);

		if (winObjectPtr != nullptr)
		{
			this->win = winObjectPtr->update(timeElapsedLastFrame);
		}
	}
}

void Level::render(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(backgroundSprite);
	for (auto* object : gameObjects)
	{
		if (object == nullptr)
		{
			continue;
		}
		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(object);

		if (characterPtr == nullptr || 
			characterPtr != nullptr && 
			characterPtr->isAlive())
		{
			gameWindow.draw(*object);
		}
	}
}

void Level::load(const std::string& levelDataPath, const int column, const int row, const sf::Vector2i& gridSize)
{
	this->win = false;
	for (auto& i : gameObjects)
	{
		delete i;
	}
	gameObjects.clear();

	this->gameObjects.resize(column * row);

	std::ifstream levelFile(levelDataPath);
	int levelObject;
	int fileCounter = 0;
	while (levelFile >> levelObject)
	{
		levelArray[fileCounter++] = levelObject;
	}
	levelFile.close();


	int levelIndex = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			GameObject* gameObjectPtr = nullptr;
			switch (/*level[levelIndex]*/ this->levelArray.data()[levelIndex])
			{
			case 0:
				break;
			case 1:
				gameObjectPtr = new Platform;
				break;
			case 2:
				gameObjectPtr = new WinObject;
				break;
			case 3:
				gameObjectPtr = new Player;
				this->playerPtr = static_cast<Player*>(gameObjectPtr);
				break;
			case 4:
				gameObjectPtr = new Enemy;
				break;
			}
			
			if (gameObjectPtr != nullptr)
			{
				gameObjectPtr->setPosition(sf::Vector2f(j * gridSize.x, i * gridSize.y)); // Why do I need to use column for y and row for x?
				gameObjects.push_back(gameObjectPtr);
			}
			gameObjectPtr = nullptr;

			levelIndex++;
		}
	}
}

void Level::reset()
{
	for (auto& i : gameObjects)
	{
		Character* characterPtr = nullptr;
		characterPtr = dynamic_cast<Character*>(i);

		if (characterPtr != nullptr)
		{
			characterPtr->resetPosition();
		}
		
		characterPtr = dynamic_cast<Enemy*>(i);
		if (characterPtr != nullptr)
		{
			characterPtr->resetLives();
		}
	}
}

Player* Level::getPlayer() const
{
	return this->playerPtr;
}

bool Level::getWin() const
{
	return this->win;
}

void Level::setBackgroundPosition(const sf::View& gameView)
{
	this->backgroundSprite.setPosition(gameView.getCenter());
	this->backgroundSprite.setScale(2.5f, 2.5f);
}
