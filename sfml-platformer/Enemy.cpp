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
	: reachedTarget(false),
	targetPosition(0.0f)
{
	this->alive = true;

	spriteRect = sf::IntRect(0, 0, 96, 84);
	this->animationPtr = new Animation(spriteRect);

	texture.loadFromFile(ASSETS_DIRECTORY + "playerSheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(spriteRect.width / 2.0f, spriteRect.height);

	hitBox.setSize(sf::Vector2f(24.0f, 36.0f));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	hitBox.setFillColor(sf::Color::Transparent);

	startPosition = this->getPosition();

	this->moveSpeed = 70.0f;
}

Enemy::~Enemy()
{
}

void Enemy::update(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	if (this->startPosition == sf::Vector2f(0.0f, 0.0f))
	{
		startPosition = this->getPosition();
		targetPosition = startPosition.x + 100.0f;
	}

	this->gotHit = false;

	if (this->lives == 0)
	{
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

		sprite.setTextureRect(animationPtr->updateAnimation(time.asSeconds(), state, velocity));

		// gör till funktion i character?
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
}
