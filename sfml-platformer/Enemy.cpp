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
		if (this->getPosition().x > startPosition)
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

void Enemy::collisionControl(const sf::Time& time, const std::vector<GameObject*>& gameObjects)
{
	this->grounded = false;
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = hitBox.getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += velocity.x * time.asSeconds();
	nextUpdateBounds.top += velocity.y * time.asSeconds() + collisionOffset;

	for (auto* i : gameObjects)
	{
		sf::FloatRect otherBounds = i->getSprite().getGlobalBounds();

		if (otherBounds.intersects(nextUpdateBounds))
		{
			GameObject* typePtr = nullptr;
			typePtr = dynamic_cast<Platform*>(i);

			if (typePtr != nullptr)
			{
				collisionPlatform(hitBoxBounds, otherBounds);
			}

		}
	}
}

Enemy::Enemy()
	: reachedTarget(false)
{
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

	setPosition(sf::Vector2f(400.0f, 0.0f));
	startPosition = this->getPosition().x;
	targetPosition = startPosition + 300.0f;

	this->moveSpeed = 70.0f;
}

Enemy::~Enemy()
{
}

void Enemy::update(const sf::Time& time, const std::vector<GameObject*>& gameObjects)
{
	patrol(time);

	if (!grounded)
	{
		velocity.y += gravity * time.asSeconds();
	}

	collisionControl(time, gameObjects);

	sprite.setTextureRect(enemyAnimation->updateAnimation(state, velocity, time.asSeconds()));

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

	//Debug
	std::cout << std::endl << std::endl;
	std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
	std::cout << "Grounded: " << grounded << std::endl;
	std::cout << "State: " << state << std::endl;
	std::cout << "Position: " << getPosition().x << ", " << getPosition().y << std::endl;
	std::cout << "Start position: " << startPosition << std::endl;
	std::cout << "Target position: " << targetPosition << std::endl;
	std::cout << "Lives: " << this->lives << std::endl;
}
