#include "WinObject.h"
#include <iostream>

WinObject::WinObject()
	: win(false)
{
	spriteRect = sf::IntRect(0, 0, 32, 32);
	animationPtr = new Animation(spriteRect);
	this->texture.loadFromFile(ASSETS_DIRECTORY + "portalSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteRect);
	this->sprite.setOrigin(this->spriteRect.width / 2.0f, spriteRect.height);

	this->hitBox.setSize(sf::Vector2f(spriteRect.getSize().x , spriteRect.getSize().y));
	hitBox.setOrigin(hitBox.getSize().x / 2.0f, hitBox.getSize().y);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->sprite.setScale(1.75f, 1.75f);
	this->hitBox.setScale(1.0f, 1.75f);

	//// Make hitbox visible
	//this->hitBox.setOutlineColor(sf::Color::Red);
	//this->hitBox.setOutlineThickness(1.0f);

	this->setPosition(sf::Vector2f(950, 632));
}

WinObject::~WinObject()
{
}

void WinObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->hitBox);
}

bool WinObject::update(sf::Time time)
{
	sprite.setTextureRect(animationPtr->updateAnimation(time.asSeconds(), "portal"));
	
	if (this->win)
	{
		this->win = false;
		return true;
	}

	return false;
}

void WinObject::setWin(bool win)
{
	this->win = win;
}
