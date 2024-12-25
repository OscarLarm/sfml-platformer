#include "Player.h"
#include <iostream>
#include <string>

Player::Player()
	: spriteRect(0, 0, 96, 84),
	moveSpeed(125.0f),
	velocity(0.0f,0.0f),
	gravity(900.0f),
	jumpForce(-350.0f),
	grounded(false),
	playerAnimation(new Animation(spriteRect)),
	playerState("none"),
	facingRight(true)
{
	this->texture.loadFromFile(this->ASSETS_DIRECTORY + "playerSheetCombat.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteRect);
	this->sprite.setOrigin(this->spriteRect.width / 2, this->spriteRect.height / 2);
	this->sprite.setPosition(sf::Vector2f(50.0f, 400.0f));
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void Player::controller(const sf::Time& time)
{
	// GRAVITY
	if (!grounded)
	{
		velocity.y += gravity * time.asSeconds();
	}

	// MOVEMENT
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		velocity.x = moveSpeed;
		playerState = "running";
		if (!facingRight)
		{
			sprite.scale(-1.0f, 1.0f); // Flips sprite
			facingRight = true;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		velocity.x = -moveSpeed;
		playerState = "running";
		if (facingRight)
		{
			sprite.scale(-1.0f, 1.0f); // Flips sprite
			facingRight = false;
		}
	}
	else
	{
		velocity.x = 0;
		playerState = "idle";
	}
	if (!grounded)
	{
		playerState = "jumping";
	}

	sprite.setTextureRect(playerAnimation->updateAnimation(playerState, velocity, time.asSeconds()));
	sprite.move(velocity * time.asSeconds());
	std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl; // For debugging

	// Collision for window borders
	// TODO: Change collision to check for sprite intersect.
	if (this->getPosition().y >= 650.0f)
	{
		grounded = true;
		velocity.y = 0;
	}
	else
	{
		grounded = false;
	}
	if (this->getPosition().x <= 0.0f)
	{
		this->setPosition(sf::Vector2f(0.0f, this->getPosition().y));
		velocity.x = 0;
	}
	if (this->getPosition().x >= 1366.0f)
	{
		this->setPosition(sf::Vector2f(1366.0f, this->getPosition().y));
		velocity.x = 0;
	}
}

void Player::jump(const sf::Time& time)
{
	if (grounded)
	{
		velocity.y = jumpForce;
		grounded = false;
	}
}

sf::Vector2f Player::getPosition() const // FOR DEBUGGING
{
	return this->sprite.getPosition();
}

sf::Vector2f Player::getVelocity() const
{
	return this->velocity;
}

sf::Sprite Player::getSprite() const
{
	return this->sprite;
}

void Player::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
}
