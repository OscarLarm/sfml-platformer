#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Character.h"
#include "Animation.h"

class Enemy : public Character
{
private:
	float startPosition;
	float targetPosition;
	bool reachedTarget;
	
	Animation* enemyAnimation;


	void patrol(const sf::Time& time);
	void collisionControl(const sf::Time& time, const std::vector<GameObject*>& gameObjects) override;

public:
	Enemy();
	~Enemy();

	void update(const sf::Time& time, const std::vector<GameObject*>& gameObjects) override;

};

#endif // !ENEMY_H
