#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Hud.h"
#include "WinObject.h"

#include <vector>

class Level
{
private:
	std::vector<GameObject*> gameObjects;

	Player* playerPtr;
	float timer;

	Hud* hud;
	
	bool win;

	//sf::View* gameCamera;

public:
	Level();
	~Level();

	void update(const sf::Time& timeElapsedLastFrame);
	void render(sf::RenderWindow& gameWindow);
	void load();
	void reset();

	Player* getPlayer() const;
	bool getWin() const;
	float getTimer() const;

	//sf::View* getGameCamera() const;
};

#endif // !LEVEL_H
