#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Enemy.h"
#include "WinObject.h"

#include "Sword.h"
class Sword;

class Player : public Character
{
private:
	const float JUMP_FORCE = -350.0f;
	const float PLAYER_LIVES = 3;
	const float PLAYER_MOVESPEED = 150.0f;
	const float SWORD_COOLDOWN = 0.5f;
	const float PLAYER_HIT_INVINCIBLE_TIME = 0.1f;

	Sword* sword;
	float swordCooldownTimer;
	bool swordReady;

	float playerHitTimer;

	void playerControls(const sf::Time& time);
	void collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects) override;

public:
	Player();
	virtual ~Player();

	void update(const sf::Time& time, std::vector<GameObject*>& gameObjects) override;
};

#endif // !PLAYER_H
