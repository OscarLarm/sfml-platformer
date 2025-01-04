#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
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

GameObject* GameObject::getGameObject(const GameObject& gameObject, std::vector<GameObject*>& gameObjectVector)
{
	return nullptr;
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
	this->hitBox.setPosition(position);
}
