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

void GameObject::setGameObject(std::string textureFileName, sf::IntRect spriteRect, sf::Vector2f hitBoxSize)
{
	this->spriteRect = spriteRect;
	this->texture.loadFromFile(this->ASSETS_DIRECTORY + textureFileName);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteRect);
	this->sprite.setOrigin(this->spriteRect.width / 2.0f, this->spriteRect.height);

	this->hitBox.setSize(hitBoxSize);
	this->hitBox.setOrigin(hitBoxSize.x / 2.0f, hitBoxSize.y);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->animationPtr = new Animation(this->spriteRect);
}

void GameObject::updateAnimation(sf::Time time, std::string currentState, sf::Vector2f velocity)
{
	this->sprite.setTextureRect(this->animationPtr->update(time.asSeconds(), currentState, velocity));
}

void GameObject::setHitBoxSize(sf::Vector2f size)
{
	this->hitBox.setSize(size);
}

void GameObject::setHitBoxOrigin(sf::Vector2f position)
{
	this->hitBox.setOrigin(position);
}

void GameObject::setHitBoxScale(sf::Vector2f scale)
{
	this->hitBox.scale(scale);
}

void GameObject::setHitBoxPosition(sf::Vector2f position)
{
	this->hitBox.setPosition(position);
}

void GameObject::setSpriteScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void GameObject::setSpritePosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

void GameObject::setScale(const sf::Vector2f& scale)
{
	this->sprite.setScale(scale);
	this->hitBox.setScale(scale);

	//TODO: Make sword class scale.
}
