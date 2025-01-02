#include "Character.h"

void Character::collisionPlatform(const sf::FloatRect& hitBoxBounds, const sf::FloatRect& platformBounds)
{
	// Vectical collision
	if (
		hitBoxBounds.top < platformBounds.top &&
		hitBoxBounds.top + hitBoxBounds.height < platformBounds.top + platformBounds.height &&
		hitBoxBounds.left < platformBounds.left + platformBounds.width &&
		hitBoxBounds.left + hitBoxBounds.width > platformBounds.left)
	{
		velocity.y = 0.0f;
		this->setPosition(sf::Vector2f(this->getPosition().x, platformBounds.top));
		this->grounded = true;
	}
	else if (
		hitBoxBounds.top > platformBounds.top &&
		hitBoxBounds.top + hitBoxBounds.height > platformBounds.top + platformBounds.height &&
		hitBoxBounds.left < platformBounds.left + platformBounds.width &&
		hitBoxBounds.left + hitBoxBounds.width > platformBounds.left)
	{
		velocity.y = 0.0f;
		this->setPosition(sf::Vector2f(this->getPosition().x, platformBounds.top + platformBounds.height + hitBoxBounds.height));
	}

	// Horizontal collision
	if (
		hitBoxBounds.left < platformBounds.left &&
		hitBoxBounds.left + hitBoxBounds.width < platformBounds.left + platformBounds.width &&
		hitBoxBounds.top < platformBounds.top + platformBounds.height &&
		hitBoxBounds.top + hitBoxBounds.height > platformBounds.top)
	{
		velocity.x = 0.0f;
		this->setPosition(sf::Vector2f(platformBounds.left - hitBoxBounds.width / 2, this->getPosition().y));
	}
	else if (
		hitBoxBounds.left > platformBounds.left &&
		hitBoxBounds.left + hitBoxBounds.width > platformBounds.left + platformBounds.width &&
		hitBoxBounds.top < platformBounds.top + platformBounds.height &&
		hitBoxBounds.top + hitBoxBounds.height > platformBounds.top)
	{
		velocity.x = 0.0f;
		this->setPosition(sf::Vector2f(platformBounds.left + platformBounds.width + hitBoxBounds.width / 2, this->getPosition().y));
	}
}



Character::Character()
	: velocity(0, 0),
	moveSpeed(125.0f),
	gravity(900.0f),
	grounded(false),
	state("none"),
	facingRight(true),
	lives(1),
	alive(true)
{
}

Character::~Character()
{
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->hitBox);
}

void Character::move(const sf::Vector2f offset)
{
	this->sprite.setPosition(this->sprite.getPosition() + offset);
	this->hitBox.setPosition(hitBox.getPosition() + offset);
}

void Character::hit(const int damage)
{
	this->lives -= damage;
}

sf::Vector2f Character::getVelocity() const
{
	return this->velocity;
}

int Character::getLives() const
{
	return this->lives;
}

bool Character::isAlive() const
{
	return this->alive;
}
