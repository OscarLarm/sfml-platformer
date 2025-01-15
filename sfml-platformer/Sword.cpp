#include "Sword.h"

Sword::Sword()
	: attacking(false),
	attackTimer(0.0f),
	lastFacingRight(true)
{
	setHitBoxSize(sf::Vector2f(40.0f, 38.0f));
	setHitBoxOrigin(sf::Vector2f(0.0f, this->getHitBox().getSize().y));
}

Sword::~Sword()
{
}

void Sword::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->getHitBox());
}

void Sword::update(const sf::Time& time, const bool facingRight, std::vector<std::unique_ptr<GameObject>>& gameObjects)
{
	if (attacking)
	{
		attackTimer += time.asSeconds();

		for (auto& i : gameObjects)
		{
			if (i == nullptr)
			{
				continue;
			}

			sf::FloatRect swordBounds = this->getHitBox().getGlobalBounds();
			sf::FloatRect enemyBounds = i->getHitBox().getGlobalBounds();
			Enemy* enemyPtr = dynamic_cast<Enemy*>(i.get());

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
			this->setHitBoxScale(sf::Vector2f(-1.0f, 1.0f));
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
