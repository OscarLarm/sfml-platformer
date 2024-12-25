#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player : public sf::Drawable
{
private:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;

	float moveSpeed;
	sf::Vector2f velocity;

	float gravity;
	float jumpForce;
	bool grounded;
	Animation* playerAnimation;

	std::string playerState;
	bool facingRight;

public:
	Player();
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void controller(const sf::Time& time);
	void jump(const sf::Time& time);

	sf::Vector2f getPosition() const; 
	sf::Vector2f getVelocity() const;
	sf::Sprite getSprite() const;

	void setPosition(const sf::Vector2f& position);
};

#endif // !PLAYER_H
