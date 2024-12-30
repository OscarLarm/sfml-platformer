#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

#include "Platform.h"
#include <vector>
#include "GameObject.h"

class Player : public GameObject
{
private:
	float moveSpeed;
	sf::Vector2f velocity;

	float gravity;
	float jumpForce;
	bool grounded;
	Animation* playerAnimation;

	std::string playerState;
	bool facingRight;

	void collision(const std::vector<Platform>& platforms, const sf::Time& time);

public:
	Player();
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void move(const sf::Vector2f offset); // Possibly make override transformable

	void controller(const sf::Time& time, const std::vector<Platform>& platforms);

	sf::Vector2f getVelocity() const;

};

#endif // !PLAYER_H
