#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

#include "Platform.h"
#include <vector>
#include "GameObject.h"
#include "Character.h"

class Player : public Character
{
private:
	float jumpForce;
	Animation* playerAnimation;


	void playerControls(const sf::Time& time);
	void collisionControl(const std::vector<Platform>& platforms, const sf::Time& time) override;

public:
	Player();
	~Player();

	void update(const sf::Time& time, const std::vector<Platform>& platforms) override;


};

#endif // !PLAYER_H
