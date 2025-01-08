#include "Player.h"
#include <iostream>
#include <string>

void Player::playerControls(const sf::Time& time)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		velocity.x = moveSpeed;
		if (grounded && !sword->isAttacking())
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
		if (grounded && !sword->isAttacking())
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
		if (grounded && !sword->isAttacking())
		{
			state = "idle";
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		velocity.y = jumpForce;
		grounded = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && swordReady)
	{
		if (state == "running")
		{
			state = "running-attack";
		}
		else if (state == "jumping")
		{
			state = "jumping-attack";
		}
		else
		{
			state = "idle-attack";
		}

		this->sword->attack();
		swordReady = false;
	}
	if (!swordReady)
	{
		swordCooldownTimer += time.asSeconds();
		if (swordCooldownTimer >= swordCooldown)
		{
			swordReady = true;
			swordCooldownTimer = 0.0f;
		}
	}
}

void Player::collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	this->grounded = false;
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = hitBox.getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += velocity.x * time.asSeconds();
	nextUpdateBounds.top += velocity.y * time.asSeconds() + collisionOffset;

	for (auto* i : gameObjects)
	{
		if (i == nullptr)
		{
			continue;
		}
		sf::FloatRect otherBounds = i->getHitBox().getGlobalBounds();

		if (otherBounds.intersects(nextUpdateBounds))
		{
			GameObject* typePtr = nullptr;
			typePtr = dynamic_cast<Platform*>(i);
	
			if (typePtr != nullptr)
			{
				collisionPlatform(hitBoxBounds, otherBounds);
			}
			else
			{
				typePtr = dynamic_cast<WinObject*>(i);

				if (typePtr != nullptr)
				{
					typePtr->setWin(true);
				}
			}
		}
	}
	if (nextUpdateBounds.top > 900) // TODO: Change to actual level-height, not hardcoded
	{
		this->hit();
	}
}

Player::Player()
	:
	jumpForce(-350.0f),
	swordCooldown(0.5f),
	swordCooldownTimer(0.0f),
	swordReady(true)
{
	this->lives = 3;
	this->startLives = this->lives;
	this->alive = true;
	spriteRect = sf::IntRect(0, 0, 96, 84);
	playerAnimation = new Animation(spriteRect);
	this->sword = new Sword;

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
	this->setStartPosition(this->getPosition());
}

Player::~Player()
{
}

void Player::update(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	this->gotHit = false;
	
	if (this->lives == 0)
	{
		// NOTE: Later add a die() function which first plays a animation, and then sets alive to false once the animation is done.
		this->alive = false;
		return;
	}
	else
	{
		this->alive = true;

		playerControls(time);
		sword->update(time, facingRight, gameObjects);

		if (!grounded)
		{
			velocity.y += gravity * time.asSeconds();

			if (!sword->isAttacking())
			{
				state = "jumping";
			}
		}

		sprite.setTextureRect(playerAnimation->updateAnimation(time.asSeconds(), state, velocity));

		collisionControl(time, gameObjects);

		this->move(velocity * time.asSeconds());
		this->sword->setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y));

	}
	

	////Debug
	//std::system("cls");
	//std::cout << std::endl << std::endl;
	//std::cout << "------PLAYER------" << std::endl;
	//std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
	//std::cout << "Grounded: " << grounded << std::endl;
	//std::cout << "State: " << state << std::endl;
	//std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
	//std::cout << "Lives: " << this->lives << std::endl;
	//std::cout << "Sword Ready: " << this->swordReady << std::endl;
	//std::cout << "Sword CD: " << this->swordCooldown - this->swordCooldownTimer << std::endl;
	//std::cout << "Start position: " << this->startPosition.x << ", " << this->startPosition.y << std::endl;
	//std::cout << "------------------" << std::endl;
}

Sword* Player::getSword() const
{
	return this->sword;
}

void Player::resetState()
{
	this->alive = true;
	this->lives = startLives;
	this->setPosition(startPosition);
}
