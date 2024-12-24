#include "Player.h"
#include <iostream>
#include <string>

void Player::updateAnimation(sf::Time time)
{
	this->animationTimer += time.asSeconds();

	if (this->currentState != this->previousState ||
		currentState == "jumping")
	{
		this->animationFrame.left = 0;
	
		if (this->currentState == "jumping")
		{
			if (this->velocity.y < -40.0f)
			{
				this->numOfFrames = 1;
				this->row = 6;
				this->animationSpeed = 0.01f;
			}
			else if (this->velocity.y <= 60.0f && this->velocity.y >= -40.0f)
			{
				this->numOfFrames = 1;
				this->row = 7;
				this->animationSpeed = 0.01f;
			}
			else if (this->velocity.y > 60.0f)
			{
				this->numOfFrames = 1;
				this->row = 8;
				this->animationSpeed = 0.01f;
			}
		}
		else if (this->currentState == "idle")
		{
			this->numOfFrames = 7;
			this->row = 1;
			this->animationSpeed = 0.09f;
		}
		else if (this->currentState == "running")
		{
			this->numOfFrames = 8;
			this->row = 3;
			this->animationSpeed = 0.08f;
		}
	}
	this->animationFrame.top = 48 * (this->row - 1);


	if (this->animationTimer >= this->animationSpeed)
	{
		if (this->animationFrame.left == 48 * (this->numOfFrames - 1))
		{
			this->animationFrame.left = 0;
		}
		else
		{
			this->animationFrame.left += 48;
		}
		this->sprite.setTextureRect(this->animationFrame);
		this->animationTimer = 0.0f;
	}
}

Player::Player()
	: moveSpeed(125.0f),
	animationTimer(0.0f),
	size(48, 48),
	facingRight(true)
{

	this->animationFrame = sf::IntRect(0, 0, this->size.x, this->size.y);
	this->texture.loadFromFile(this->ASSETS_DIRECTORY + "playerSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->animationFrame);
	this->sprite.setOrigin(this->size.x / 2, this->size.y / 2);
	this->setPosition(sf::Vector2f(50.0f, 400.0f));

	this->velocity = sf::Vector2f(0.0f, 0.0f);
	this->grounded = false;
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void Player::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
	
}

sf::Vector2f Player::getPosition() const // FOR DEBUGGING
{
	return this->sprite.getPosition();
}

sf::Sprite Player::getSprite() const
{
	return this->sprite;
}

void Player::controller(const sf::Time& time)
{

	// GRAVITY
	if (!this->grounded)
	{
		this->velocity.y += gravity * time.asSeconds();
	}

	// MOVEMENT
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && 
	!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		this->velocity.x = this->moveSpeed;
		this->currentState = "running";
		if (!facingRight)
		{
			this->sprite.scale(-1.0f, 1.0f);
			this->facingRight = true;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		this->velocity.x = - this->moveSpeed;
		this->currentState = "running";
		if (facingRight)
		{
			this->sprite.scale(-1.0f, 1.0f);
			this->facingRight = false;
		}
	}
	else
	{
		this->velocity.x = 0;
		this->currentState = "idle";
	}
	if (!grounded)
	{
		this->currentState = "jumping";
	}

	this->sprite.move(velocity * time.asSeconds());
	std::cout << velocity.x << ", " << velocity.y << std::endl;
	this->updateAnimation(time);
	this->previousState = this->currentState;

	// Collision for window borders
	// TODO: Change collision to check for sprite intersect.
	if (this->getPosition().y >= 650.0f)
	{
		this->grounded = true;
		velocity.y = 0;
	}
	else
	{
		grounded = false;
	}
	if (this->getPosition().x <= 0.0f)
	{
		this->setPosition(sf::Vector2f(0.0f, this->getPosition().y));
		this->velocity.x = 0;
	}
	if (this->getPosition().x >= 1366.0f - this->getSprite().getGlobalBounds().width)
	{
		this->setPosition(sf::Vector2f(1366.0f - this->getSprite().getGlobalBounds().width, this->getPosition().y));
		this->velocity.x = 0;
	}

	// ANIMATION
}

void Player::jump(const sf::Time& time)
{
	if (grounded)
	{
		this->velocity.y = this->jumpForce;
		this->grounded = false;
	}
}
