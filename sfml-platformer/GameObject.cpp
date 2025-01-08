#include "GameObject.h"

void GameObject::setWin(bool win)
{
}

bool GameObject::getWin() const
{
	return false;
}

GameObject::GameObject()
	: hitBox(sf::Vector2f(32.0f, 32.0f)),
	animationPtr(nullptr)

{
}

GameObject::~GameObject()
{
	delete this->animationPtr;
}

sf::Vector2f GameObject::getPosition() const
{
	return this->hitBox.getPosition();
}

sf::Sprite GameObject::getSprite() const
{
	return this->sprite;
}

sf::RectangleShape GameObject::getHitBox() const
{
	return this->hitBox;
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
	this->hitBox.setPosition(position);
}

void GameObject::setScale(const sf::Vector2f& scale)
{
	this->sprite.setScale(scale);
	this->hitBox.setScale(scale);

	//TODO: Make sword class scale.
}
