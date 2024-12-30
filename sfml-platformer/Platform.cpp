#include "Platform.h"

Platform::Platform() 
	: spriteRect(32, 16, 16, 16)
{
	this->texture.loadFromFile(ASSETS_DIRECTORY + "tileSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteRect);

	this->sprite.setOrigin(this->spriteRect.width / 2.0f, spriteRect.height);
	this->sprite.setPosition(150, 650);



	this->hitBox.setSize(sf::Vector2f(spriteRect.getSize().x, spriteRect.getSize().y));
	this->hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setPosition(this->sprite.getPosition());

	//// Make hitbox visible
	//this->hitBox.setOutlineColor(sf::Color::Red);
	//this->hitBox.setOutlineThickness(1.0f);
}

Platform::~Platform()
{
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->hitBox);
}

sf::Sprite Platform::getSprite() const
{
	return this->sprite;
}

void Platform::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
	hitBox.setPosition(this->sprite.getPosition());

}
