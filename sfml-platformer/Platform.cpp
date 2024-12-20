#include "Platform.h"

Platform::Platform(sf::Vector2f position)
{
	this->texture.loadFromFile("../assets/platform.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->position = position;
	this->sprite.setPosition(this->position);
}

Platform::~Platform()
{
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void Platform::setPosition(const sf::Vector2f& position)
{
}
