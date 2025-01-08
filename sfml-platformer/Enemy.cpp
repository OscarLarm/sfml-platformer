#include "Enemy.h"
#include <iostream>

void Enemy::patrol(const sf::Time& time)
{
	if (!reachedTarget)
	{
		if (this->getPosition().x < targetPosition)
		{
			this->velocity.x = moveSpeed;
			state = "patrol";
		}
		else
		{
			this->velocity.x = 0.0f;
			state = "idle";
			reachedTarget = true;
		}
	}
	else if (reachedTarget)
	{
		if (this->getPosition().x > startPosition.x)
		{
			this->velocity.x = -moveSpeed;
			state = "patrol";
		}
		else
		{
			this->velocity.x = 0.0f;
			state = "idle";
			reachedTarget = false;
		}
	}
}

void Enemy::collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	this->grounded = false;
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = hitBox.getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += velocity.x * time.asSeconds();
	nextUpdateBounds.top += velocity.y * time.asSeconds() + collisionOffset;

	for (auto* i : gameObjects)
	{
		if (i != nullptr)
		{
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
					Player* playerPtr = dynamic_cast<Player*>(i);

					if (playerPtr != nullptr && !playerPtr->isHit())
					{
						playerPtr->hit();
					}
				}
			}
		}
	}
}

Enemy::Enemy()
	: reachedTarget(false)
{
	this->alive = true;

	spriteRect = sf::IntRect(0, 0, 96, 84);
	enemyAnimation = new Animation(spriteRect);

	texture.loadFromFile(ASSETS_DIRECTORY + "playerSheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(spriteRect.width / 2.0f, spriteRect.height);

	hitBox.setSize(sf::Vector2f(24.0f, 36.0f));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	hitBox.setFillColor(sf::Color::Transparent);

	//// Make hitbox visible
	//hitBox.setOutlineColor(sf::Color::Red);
	//hitBox.setOutlineThickness(1.0f);
	
	this->setStartPosition(this->getPosition());
	setPosition(startPosition);
	targetPosition = startPosition.x + 20.0f;

	this->moveSpeed = 70.0f;
}

Enemy::~Enemy()
{
}

void Enemy::update(const sf::Time& time, std::vector<GameObject*>& gameObjects)
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

		patrol(time);

		if (!grounded)
		{
			velocity.y += gravity * time.asSeconds();
		}

		collisionControl(time, gameObjects);

		sprite.setTextureRect(enemyAnimation->updateAnimation(time.asSeconds(), state, velocity));

		if (this->velocity.x < 0 && facingRight == true)
		{
			facingRight = false;
			this->sprite.scale(-1.0f, 1.0f);
		}
		else if (this->velocity.x > 0 && facingRight == false)
		{
			facingRight = true;
			this->sprite.scale(-1.0f, 1.0f);
		}

		this->move(velocity * time.asSeconds());
	}

	////Debug
	//std::cout << std::endl << std::endl;
	//std::cout << "------ENEMY------" << std::endl;
	//std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
	//std::cout << "Grounded: " << grounded << std::endl;
	//std::cout << "State: " << state << std::endl;
	//std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
	//std::cout << "Start position: " << startPosition.x << ", " << startPosition.y << std::endl;
	//std::cout << "Target position: " << targetPosition << std::endl;
	//std::cout << "Lives: " << this->lives << std::endl;
	//std::cout << "Alive: " << this->alive << std::endl;
	//std::cout << "-----------------" << std::endl;
}

