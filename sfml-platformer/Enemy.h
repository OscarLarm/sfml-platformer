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
	void collisionControl(const std::vector<Platform*>& platforms, const sf::Time& time) override;

public:
	Enemy();
	~Enemy();

	void update(const sf::Time& time, const std::vector<Platform*>& platforms) override;

};

#endif // !ENEMY_H
