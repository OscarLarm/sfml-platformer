#include "GameObject.h"

void GameObject::setWin(const bool win){

}

bool GameObject::getWin() const
{
	return false;
}

GameObject::GameObject()
	: hitBox(sf::Vector2f(32.0f, 32.0f)),
	animationPtr(nullptr),
	currentState(Animation::States::Idle)
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

Animation::States GameObject::getCurrentState() const
{
	return this->currentState;
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

void GameObject::setGameObjectValues(const std::string& textureFileName, const sf::IntRect& spriteRect, const sf::Vector2f& hitBoxSize)
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

void GameObject::updateAnimation(const sf::Time& time, const Animation::States currentState, const sf::Vector2f& velocity)
{
	this->sprite.setTextureRect(this->animationPtr->update(time.asSeconds(), currentState, velocity));
}

void GameObject::setHitBoxSize(const sf::Vector2f& size)
{
	this->hitBox.setSize(size);
}

void GameObject::setHitBoxOrigin(const sf::Vector2f& position)
{
	this->hitBox.setOrigin(position);
}

void GameObject::setHitBoxScale(const sf::Vector2f& scale)
{
	this->hitBox.scale(scale);
}

void GameObject::setHitBoxPosition(const sf::Vector2f& position)
{
	this->hitBox.setPosition(position);
}

void GameObject::setSpriteScale(const sf::Vector2f& scale)
{
	this->sprite.setScale(scale);
}

void GameObject::setSpritePosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
}

void GameObject::setCurrentState(const Animation::States state)
{
	this->currentState = state;
}

void GameObject::setScale(const sf::Vector2f& scale)
{
	this->sprite.setScale(scale);
	this->hitBox.setScale(scale);
}
