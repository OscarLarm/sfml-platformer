#include "Player.h"
#include <iostream>
#include <string>

void Player::collision(const std::vector<Platform>& platforms, const sf::Time& time)
{
	this->grounded = false;
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = hitBox.getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += velocity.x * time.asSeconds();
	nextUpdateBounds.top += velocity.y * time.asSeconds() + collisionOffset;

	for (const Platform& i : platforms)
	{
		sf::FloatRect platformBounds = i.getSprite().getGlobalBounds();

		if (platformBounds.intersects(nextUpdateBounds))
		{
			// Vectical collision
			if (
				hitBoxBounds.top < platformBounds.top &&
				hitBoxBounds.top + hitBoxBounds.height < platformBounds.top + platformBounds.height &&
				hitBoxBounds.left < platformBounds.left + platformBounds.width &&
				hitBoxBounds.left + hitBoxBounds.width > platformBounds.left)
			{
				velocity.y = 0.0f;
				this->setPosition(sf::Vector2f(this->getPosition().x, platformBounds.top - collisionOffset));
				this->grounded = true;
			}
			else if (
				hitBoxBounds.top > platformBounds.top &&
				hitBoxBounds.top + hitBoxBounds.height > platformBounds.top + platformBounds.height &&
				hitBoxBounds.left < platformBounds.left + platformBounds.width &&
				hitBoxBounds.left + hitBoxBounds.width > platformBounds.left)
			{
				velocity.y = 0.0f;
				this->setPosition(sf::Vector2f(this->getPosition().x, platformBounds.top + platformBounds.height + hitBoxBounds.height));
			}
			
			// Horizontal collision
			if (
				hitBoxBounds.left < platformBounds.left &&
				hitBoxBounds.left + hitBoxBounds.width < platformBounds.left + platformBounds.width &&
				hitBoxBounds.top < platformBounds.top + platformBounds.height &&
				hitBoxBounds.top + hitBoxBounds.height > platformBounds.top)
			{
				velocity.x = 0.0f;
				this->setPosition(sf::Vector2f(platformBounds.left - hitBoxBounds.width / 2, this->getPosition().y));
			}
			else if (
				hitBoxBounds.left > platformBounds.left &&
				hitBoxBounds.left + hitBoxBounds.width > platformBounds.left + platformBounds.width &&
				hitBoxBounds.top < platformBounds.top + platformBounds.height &&
				hitBoxBounds.top + hitBoxBounds.height > platformBounds.top)
			{
				velocity.x = 0.0f;
				this->setPosition(sf::Vector2f(platformBounds.left + platformBounds.width + hitBoxBounds.width / 2, this->getPosition().y));
			}
		}
	}
}

Player::Player()
	:
	moveSpeed(125.0f),
	velocity(0.0f,0.0f),
	gravity(900.0f),
	jumpForce(-350.0f),
	grounded(false),
	playerState("none"),
	facingRight(true)
{
	spriteRect = sf::IntRect(0, 0, 96, 84);
	playerAnimation = new Animation(spriteRect);

	texture.loadFromFile(ASSETS_DIRECTORY + "playerSheetCombat.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(spriteRect.width / 2.0f, spriteRect.height);

	hitBox.setSize(sf::Vector2f(16.0f, 36.0f));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	hitBox.setFillColor(sf::Color::Transparent);
	
	// Make hitbox visible
	hitBox.setOutlineColor(sf::Color::Red);
	hitBox.setOutlineThickness(1.0f);

	setPosition(sf::Vector2f(50.0f, 0.0f));
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
	// MOVEMENT
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		velocity.x = moveSpeed;
		if (grounded)
		{
			playerState = "running";
		}
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
		if (grounded)
		{
			playerState = "running";
		}
		if (facingRight)
		{
			sprite.scale(-1.0f, 1.0f); // Flips sprite
			facingRight = false;
		}
	}
	else
	{
		velocity.x = 0;
		if (grounded)
		{
			playerState = "idle";

		}
	}

	//Actions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		velocity.y = jumpForce;
		grounded = false;
	}

	if (!grounded)
	{
		velocity.y += gravity * time.asSeconds();
		playerState = "jumping";
	}

	sprite.setTextureRect(playerAnimation->updateAnimation(playerState, velocity, time.asSeconds()));

	collision(platforms, time); //Testing before move

	this->move(velocity * time.asSeconds());

	//Debug
	std::system("cls");
	std::cout << std::endl << std::endl;
	std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
	std::cout << "Grounded: " << grounded << std::endl;
	std::cout << "State: " << playerState << std::endl;
	std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
}

sf::Vector2f Player::getVelocity() const
{
	return this->velocity;
}

void Player::move(const sf::Vector2f offset)
{
	this->sprite.setPosition(this->sprite.getPosition() + offset);
	this->hitBox.setPosition(hitBox.getPosition() + offset);
}
