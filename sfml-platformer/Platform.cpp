#include "Platform.h"
#include <iostream>
#include <string>

Platform::Platform() 
{
	spriteRect = sf::IntRect(0, 0, 48, 16);

	this->texture.loadFromFile(ASSETS_DIRECTORY + "tileSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteRect);
	this->sprite.setOrigin(this->spriteRect.width / 2.0f, spriteRect.height);

	this->hitBox.setSize(sf::Vector2f(spriteRect.getSize().x, spriteRect.getSize().y));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	this->hitBox.setFillColor(sf::Color::Transparent);

	//// Make hitbox visible
	//this->hitBox.setOutlineColor(sf::Color::Red);
	//this->hitBox.setOutlineThickness(1.0f);

	//this->setPosition(sf::Vector2f(150, 650));
}

Platform::~Platform()
{
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->hitBox);
}

