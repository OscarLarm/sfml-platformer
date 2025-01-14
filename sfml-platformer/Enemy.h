#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
private:
	float targetPosition;
	bool reachedTarget;

	void patrol(const sf::Time& time);
	void collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects) override;

public:
	Enemy();
	virtual ~Enemy();

	void update(const sf::Time& time, std::vector<GameObject*>& gameObjects) override;

};

#endif // !ENEMY_H
