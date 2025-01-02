#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include <vector>
#include "GameObject.h"
#include "Character.h"
#include "Enemy.h"
#include "Sword.h" // TEMPORARY CHANGED TO FORWARD DECLARATION, CIRCULAR INCLUDES.

class Sword; // TEMPORARY CHANGED TO FORWARD DECLARATION, CIRCULAR INCLUDES.

class Player : public Character
{
private:
	float jumpForce;
	Animation* playerAnimation;
	
	Sword* sword;
	float swordCooldown;
	float swordCooldownTimer;
	bool swordReady;

	void playerControls(const sf::Time& time);
	void collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects) override;

public:
	Player();
	~Player();

	void update(const sf::Time& time, std::vector<GameObject*>& gameObjects) override;
	
	Sword* getSword() const;
	void hit(const int damage = 1) override;

};

#endif // !PLAYER_H
