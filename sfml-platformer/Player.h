#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

#include "Platform.h"
#include <vector>

class Player : public sf::Drawable
{
private:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	sf::RectangleShape hitBox;

	float moveSpeed;
	sf::Vector2f velocity;

	float gravity;
	float jumpForce;
	bool grounded;
	Animation* playerAnimation;

	std::string playerState;
	bool facingRight;

	void collision(const std::vector<Platform>& platforms);

public:
	Player();
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void controller(const sf::Time& time, const std::vector<Platform>& platforms);
	void jump(const sf::Time& time);

	sf::Vector2f getPosition() const; 
	sf::Vector2f getVelocity() const;
	sf::Sprite getSprite() const;

	void setPosition(const sf::Vector2f& position);

	void move(const sf::Vector2f offset); // Possibly make override transformable
};

#endif // !PLAYER_H
