#include "Enemy.h"

void Enemy::patrol(const sf::Time& time)
{
	if (!reachedTarget)
	{
		if (this->getPosition().x < targetPosition)
		{
			this->setVelocity(this->getMoveSpeed(), this->getVelocity().y);
			setCurrentState(Animation::States::Patrol);
		}
		else
		{
			this->setVelocity(0.0f, this->getVelocity().y);
			setCurrentState(Animation::States::Patrol);
			this->reachedTarget = true;
		}
	}
	else if (reachedTarget)
	{
		if (this->getPosition().x > this->getStartPosition().x)
		{
			this->setVelocity(-this->getMoveSpeed(), this->getVelocity().y);
			setCurrentState(Animation::States::Patrol);
		}
		else
		{
			this->setVelocity(0.0f, this->getVelocity().y);
			setCurrentState(Animation::States::Idle);
			this->reachedTarget = false;
		}
	}
}

void Enemy::collisionControl(const sf::Time& time, std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
	this->setGrounded(false);
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = this->getHitBox().getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += this->getVelocity().x * time.asSeconds();
	nextUpdateBounds.top += this->getVelocity().y * time.asSeconds() + collisionOffset;

	for (auto& i : gameObjects)
	{
		if (i != nullptr)
		{
			sf::FloatRect otherBounds = i->getHitBox().getGlobalBounds();

			if (otherBounds.intersects(nextUpdateBounds))
			{
				GameObject* typePtr = nullptr;
				typePtr = dynamic_cast<Platform*>(i.get());

				if (typePtr != nullptr)
				{
					collisionPlatform(hitBoxBounds, otherBounds);
				}
				else
				{
					Player* playerPtr = dynamic_cast<Player*>(i.get());

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

void Enemy::update(const sf::Time& time, std::vector<std::unique_ptr<GameObject>>& gameObjects)
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
			this->setVelocity(this->getVelocity().x, this->getVelocity().y + getGravity() * time.asSeconds());
		}

		collisionControl(time, gameObjects);

		updateAnimation(time, getCurrentState(), this->getVelocity());

		this->move(this->getVelocity() *time.asSeconds());

		//std::system("cls");
		//std::cout << "CurrentState: " << static_cast<int>(getCurrentState()) << std::endl;
	}
}
