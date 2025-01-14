#include "Player.h"

void Player::playerControls(const sf::Time& time)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		this->setVelocity(this->getMoveSpeed(), this->getVelocity().y);
		if (this->isGrounded() && !sword->isAttacking())
		{
			setCurrentState(Animation::States::Running);

		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		this->setVelocity(-this->getMoveSpeed(), this->getVelocity().y);
		if (this->isGrounded() && !sword->isAttacking())
		{
			setCurrentState(Animation::States::Running);
		}
	}
	else
	{
		this->setVelocity(0.0f, this->getVelocity().y);
		if (isGrounded() && !sword->isAttacking())
		{
			setCurrentState(Animation::States::Idle);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->isGrounded())
	{
		this->setVelocity(this->getVelocity().x, this->JUMP_FORCE);
		this->setGrounded(false);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && swordReady)
	{
		Animation::States state = getCurrentState();

		if (state == Animation::States::Running)
		{
			setCurrentState(Animation::States::RunningAttack);
		}
		else if (state == Animation::States::Jumping)
		{
			setCurrentState(Animation::States::JumpingAttack);
		}
		else
		{
			setCurrentState(Animation::States::IdleAttack);
		}

		this->sword->attack();
		this->swordReady = false;
	}
	if (!swordReady)
	{
		swordCooldownTimer += time.asSeconds();
		if (swordCooldownTimer >= SWORD_COOLDOWN)
		{
			swordReady = true;
			swordCooldownTimer = 0.0f;
		}
	}
}

void Player::collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	this->setGrounded(false);
	float collisionOffset = 1.0f;

	sf::FloatRect hitBoxBounds = this->getHitBox().getGlobalBounds();

	sf::FloatRect nextUpdateBounds = hitBoxBounds;
	nextUpdateBounds.left += this->getVelocity().x * time.asSeconds();
	nextUpdateBounds.top += this->getVelocity().y * time.asSeconds() + collisionOffset;

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
	: swordCooldownTimer(0.0f),
	swordReady(true),
	playerHitTimer(0.0f)
{
	this->setCharacterValues(PLAYER_LIVES, PLAYER_MOVESPEED);
	this->setGameObjectValues("playerSheetCombat.png", sf::IntRect(0, 0, 96, 84), sf::Vector2f(16.0f, 36.0f));

	this->sword = new Sword;

}

Player::~Player()
{
	delete this->sword;
}

void Player::update(const sf::Time& time, std::vector<GameObject*>& gameObjects)
{
	if (this->getStartPosition() == sf::Vector2f(0.0f, 0.0f))
	{
		this->setStartPosition(this->getPosition());
	}
	
	if (this->getLives() == 0)
	{
		this->setAlive(false);
		return;
	}
	else
	{
		this->playerHitTimer += time.asSeconds();

		if (playerHitTimer >= this->PLAYER_HIT_INVINCIBLE_TIME)
		{
			this->playerHitTimer = 0.0f;
			this->setHit(false);
		}
		this->setAlive(true);


		playerControls(time);
		sword->update(time, this->isFacingRight(), gameObjects);

		if (!this->isGrounded())
		{
			this->setVelocity(this->getVelocity().x, this->getVelocity().y + this->getGravity() * time.asSeconds());

			if (!sword->isAttacking())
			{
				setCurrentState(Animation::States::Jumping);
			}
		}

		updateAnimation(time, getCurrentState(), this->getVelocity());

		collisionControl(time, gameObjects);

		this->move(this->getVelocity() * time.asSeconds());
		this->sword->setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y));

		//std::system("cls");
		//std::cout << "Facingright: " << facingRight << std::endl;
	}
}
