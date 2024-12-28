#include "Player.h"
#include <iostream>
#include <string>

void Player::collision(const std::vector<Platform>& platforms, const sf::Time& time)
{
	sf::FloatRect thisBounds = hitBox.getGlobalBounds();
	sf::FloatRect nextUpdateBounds = thisBounds;
	nextUpdateBounds.left += velocity.x * time.asSeconds();
	nextUpdateBounds.top += velocity.y * time.asSeconds();

	float thisLeft = thisBounds.left;
	float thisRight = thisBounds.left + thisBounds.width;
	float thisTop = thisBounds.top;
	float thisBottom = thisBounds.top + thisBounds.height;



	
	for (const Platform& i : platforms)
	{
		sf::FloatRect platFormBounds = i.getSprite().getGlobalBounds();
		
		float platformLeft = platFormBounds.left;
		float platformRight = platFormBounds.left + platFormBounds.width;
		float platformTop = platFormBounds.top;
		float platformBottom = platFormBounds.top + platFormBounds.height;

		if (platFormBounds.intersects(nextUpdateBounds))
		{

			if (true)
			{
				std::cout << "Collision on feet" << std::endl;

			}
			else if (true)
			{
				std::cout << "Collision on head" << std::endl;
			}

			if (true)
			{
				std::cout << "Collision on right" << std::endl;
			}

			else if (true)
			{
				std::cout << "Collision on left" << std::endl;
			}

		}
	}
}

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
	this->sprite.setOrigin(this->spriteRect.width / 2.0f, spriteRect.height);

	this->hitBox.setSize(sf::Vector2f(16.0f, 36.0f));
	this->hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	this->hitBox.setFillColor(sf::Color::Transparent);
	
	// Make hitbox visible
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.0f);

	this->setPosition(sf::Vector2f(50.0f, 500.0f));
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->hitBox);
}

void Player::controller(const sf::Time& time, const std::vector<Platform>& platforms)
{
	grounded = false;
	//grounded = false;
	//collision(platforms);

	//// GRAVITY
	//if (!grounded)
	//{
	//	velocity.y += gravity * time.asSeconds();
	//}
	//else
	//{
	//	velocity.y = 0;
	//}

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

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		velocity.y = -moveSpeed;
		playerState = "running";
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{
		velocity.y = moveSpeed;
		playerState = "running";
	}
	else
	{
		velocity.y = 0;
	}

	////Actions
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	//{
	//	velocity.y = jumpForce;
	//	grounded = false;
	//}

	//if (!grounded)
	//{
	//	velocity.y += gravity * time.asSeconds();
	//}

	//if (!grounded)
	//{
	//	playerState = "jumping";
	//}


	sprite.setTextureRect(playerAnimation->updateAnimation(playerState, velocity, time.asSeconds()));
	this->move(velocity * time.asSeconds());

	collision(platforms, time);

	//Debug
	//std::cout << std::endl << std::endl;
	//std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
	//std::cout << "Grounded: " << grounded << std::endl;
	//std::cout << "State: " << playerState << std::endl;
	//std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
}

sf::Vector2f Player::getPosition() const
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
	this->hitBox.setPosition(position);
}

void Player::move(const sf::Vector2f offset)
{
	this->sprite.setPosition(this->sprite.getPosition() + offset);
	this->hitBox.setPosition(hitBox.getPosition() + offset);
}
