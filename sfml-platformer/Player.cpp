#include "Player.h"
#include <iostream>
#include <string>

void Player::playerControls(const sf::Time& time)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		velocity.x = moveSpeed;
		if (grounded)
		{
			state = "running";
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
			state = "running";
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
			state = "idle";

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		velocity.y = jumpForce;
		grounded = false;
	}
}

void Player::collisionControl(const std::vector<Platform*>& platforms, const sf::Time& time)
{
	this->grounded = false;
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = hitBox.getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += velocity.x * time.asSeconds();
	nextUpdateBounds.top += velocity.y * time.asSeconds() + collisionOffset;

	for (auto* i : platforms)
	{
		sf::FloatRect platformBounds = i->getSprite().getGlobalBounds();

		if (platformBounds.intersects(nextUpdateBounds))
		{
			collisionPlatform(hitBoxBounds, platformBounds);
		}
	}
}

Player::Player()
	:
	jumpForce(-350.0f)
{
	this->lives = 3;

	spriteRect = sf::IntRect(0, 0, 96, 84);
	playerAnimation = new Animation(spriteRect);

	texture.loadFromFile(ASSETS_DIRECTORY + "playerSheetCombat.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(spriteRect.width / 2.0f, spriteRect.height);

	hitBox.setSize(sf::Vector2f(16.0f, 36.0f));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	hitBox.setFillColor(sf::Color::Transparent);
	
	//// Make hitbox visible
	//hitBox.setOutlineColor(sf::Color::Red);
	//hitBox.setOutlineThickness(1.0f);

	setPosition(sf::Vector2f(50.0f, 0.0f));
}

Player::~Player()
{
}

void Player::update(const sf::Time& time, const std::vector<Platform*>& platforms)
{
	playerControls(time);

	if (!grounded)
	{
		velocity.y += gravity * time.asSeconds();
		state = "jumping";
	}

	sprite.setTextureRect(playerAnimation->updateAnimation(state, velocity, time.asSeconds()));

	collisionControl(platforms, time);

	this->move(velocity * time.asSeconds());

	//Debug
	std::system("cls");
	std::cout << std::endl << std::endl;
	std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
	std::cout << "Grounded: " << grounded << std::endl;
	std::cout << "State: " << state << std::endl;
	std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
	std::cout << "Lives: " << this->lives << std::endl;
}
