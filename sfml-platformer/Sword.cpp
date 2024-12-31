#include "Sword.h"
#include <iostream>

Sword::Sword()
	: attacking(false),
	attackDuration(0.25f),
	attackTimer(0.0f),
	lastFacingDirection(true)
{
	hitBox.setSize(sf::Vector2f(38.0f, 38.0f));
	hitBox.setOrigin(0.0f, this->hitBox.getSize().y);
	hitBox.setFillColor(sf::Color::Transparent);

	//// Make hitbox visible
	//hitBox.setOutlineColor(sf::Color::Red);
	//hitBox.setOutlineThickness(1.0f);

	this->setPosition(sf::Vector2f(200.0f, 200.0f));
}

Sword::~Sword()
{
}

void Sword::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->hitBox);
}

void Sword::update(const sf::Time& time, const bool facingRight)
{
	if (attacking)
	{
		//hitBox.setOutlineColor(sf::Color::White);
		attackTimer += time.asSeconds();

		if (attackTimer >= attackDuration)
		{
			this->attacking = false;
			attackTimer = 0.0f;
		}
	}
	else if(!attacking)
	{
		//hitBox.setOutlineColor(sf::Color::Red);
		if (facingRight != lastFacingDirection)
		{
			this->hitBox.scale(sf::Vector2f(-1.0f, 1.0f));
			lastFacingDirection = facingRight;

		}
	}
}

void Sword::attack()
{
	this->attacking = true;
}

void Sword::stopAttack()
{
	this->attacking = false;
}

bool Sword::isAttacking() const
{
    return this->attacking;
}
