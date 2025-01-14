#include "Enemy.h"

void Enemy::patrol(const sf::Time& time)
{
	if (!reachedTarget)
	{
		if (this->getPosition().x < targetPosition)
		{
			this->setVelocityX(this->getMoveSpeed());
			this->setState("patrol");
		}
		else
		{
			this->setVelocityX(0.0f);
			this->setState("idle");
			this->reachedTarget = true;
		}
	}
	else if (reachedTarget)
	{
		if (this->getPosition().x > this->getStartPosition().x)
		{
			this->setVelocityX(-this->getMoveSpeed());
			this->setState("patrol");

		}
		else
		{
			this->setVelocityX(0.0f);
			this->setState("idle");
			this->reachedTarget = false;
		}
	}
}

void Enemy::collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	this->setGrounded(false);
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = this->getHitBox().getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += this->getVelocity().x * time.asSeconds();
	nextUpdateBounds.top += this->getVelocity().y * time.asSeconds() + collisionOffset;

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
	this->setCharacterValues(ENEMY_LIVES, ENEMY_MOVESPEED);
	setGameObjectValues("playerSheet.png", sf::IntRect(0, 0, 96, 84), sf::Vector2f(24.0f, 36.0f));
}

Enemy::~Enemy()
{
}

void Enemy::update(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	if (this->getStartPosition() == sf::Vector2f(0.0f, 0.0f))
	{
		this->setStartPosition(this->getPosition());
		this->targetPosition = this->getStartPosition().x + 100.0f;
	}

	this->setHit(false);

	if (this->getLives() == 0)
	{
		this->setAlive(false);
		return;
	}
	else
	{
		this->setAlive(true);

		patrol(time);

		if (!this->isGrounded())
		{
			this->setVelocityY(this->getVelocity().y + getGravity() * time.asSeconds());
			//velocity.y += gravity * time.asSeconds();
		}

		collisionControl(time, gameObjects);

		updateAnimation(time, this->getState(), this->getVelocity());

		//// g�r till funktion i character?
		//if (this->velocity.x < 0 && facingRight == true)
		//{
		//	facingRight = false;
		//	this->setSpriteScale(sf::Vector2f(-1.0f, 1.0f));
		//}
		//else if (this->velocity.x > 0 && facingRight == false)
		//{
		//	facingRight = true;
		//	this->setSpriteScale(sf::Vector2f(1.0f, 1.0f));
		//}

		this->move(this->getVelocity() *time.asSeconds());
	}
}
