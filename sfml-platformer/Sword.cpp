#include "Sword.h"

Sword::Sword()
	: attacking(false),
	attackTimer(0.0f),
	lastFacingRight(true)
{
	hitBox.setSize(sf::Vector2f(40.0f, 38.0f));
	hitBox.setOrigin(0.0f, this->hitBox.getSize().y);
	hitBox.setFillColor(sf::Color::Transparent);

	this->setPosition(sf::Vector2f(200.0f, 200.0f));
}

Sword::~Sword()
{
}

void Sword::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->hitBox);
}

void Sword::update(const sf::Time& time, const bool facingRight, std::vector<GameObject*>& gameObjects)
{
	if (attacking)
	{
		attackTimer += time.asSeconds();

		for (auto* i : gameObjects)
		{
			if (i == nullptr)
			{
				continue;
			}

			sf::FloatRect swordBounds = this->hitBox.getGlobalBounds();
			sf::FloatRect enemyBounds = i->getHitBox().getGlobalBounds();
			Enemy* enemyPtr = dynamic_cast<Enemy*>(i);

			if (enemyBounds.intersects(swordBounds) && enemyPtr != nullptr && enemyPtr->isAlive())
			{
				enemyPtr->hit(this->DAMAGE);
			}
		}

		if (attackTimer >= ATTACK_DURATION)
		{
			this->attacking = false;
			attackTimer = 0.0f;
		}
	}
	else if(!attacking)
	{
		if (facingRight != lastFacingRight)
		{
			this->hitBox.scale(sf::Vector2f(-1.0f, 1.0f));
			lastFacingRight = facingRight;

		}
	}
}

void Sword::attack()
{
	this->attacking = true;
}

bool Sword::isAttacking() const
{
    return this->attacking;
}
