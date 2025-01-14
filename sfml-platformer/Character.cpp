#include "Character.h"

void Character::collisionPlatform(const sf::FloatRect& hitBoxBounds, const sf::FloatRect& platformBounds)
{
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

void Character::flip()
{
	if (this->velocity.x > 0.0f)
	{
		this->facingRight = true;
		this->setSpriteScale(sf::Vector2f(1.0f, 1.0f));
	}
	else if (this->velocity.x < 0.0f)
	{
		this->facingRight = false;
		this->setSpriteScale(sf::Vector2f(-1.0f, 1.0f));
	}
}

float Character::getMoveSpeed() const
{
	return this->moveSpeed;
}

void Character::setVelocity(const float x, const float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}

bool Character::isGrounded() const
{
	return this->grounded;
}

void Character::setGrounded(const bool grounded)
{
	this->grounded = grounded;
}

void Character::setCharacterValues(const int lives, const float moveSpeed)
{
	this->startLives = lives;
	this->lives = startLives;
	this->moveSpeed = moveSpeed;
}

void Character::setAlive(const bool alive)
{
	this->alive = alive;
}

void Character::setHit(bool hit)
{
	this->gotHit = hit;
}

bool Character::isFacingRight() const
{
	return this->facingRight;
}

float Character::getGravity() const
{
	return this->GRAVITY;
}

void Character::setStartPosition(const sf::Vector2f& position)
{
	this->startPosition = position;
}

sf::Vector2f Character::getStartPosition() const
{
	return this->startPosition;
}



Character::Character()
	: velocity(0, 0),
	moveSpeed(0.0f),
	grounded(true),
	facingRight(true),
	lives(0),
	startLives(this->lives),
	alive(true),
	gotHit(false),
	startPosition(sf::Vector2f(0.0f, 0.0f))
{
}

Character::~Character()
{
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->getSprite());
	target.draw(this->getHitBox());
}

void Character::move(const sf::Vector2f& offset)
{
	this->setSpritePosition(this->getSprite().getPosition() + offset);
	this->setHitBoxPosition(this->getHitBox().getPosition() + offset);

	this->flip();
}

void Character::resetPosition()
{
	this->setPosition(startPosition);
	this->velocity = sf::Vector2f(0.0f, 0.0f);
}

void Character::resetLives()
{
	this->lives = startLives;
}

void Character::hit(const int damage)
{
	if (this->isAlive() && this->gotHit == false)
	{
		this->gotHit = true;
		this->lives -= damage;
	}
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

bool Character::isHit() const
{
	if (this == nullptr)
	{
		return false;
	}
	return this->gotHit;
}
