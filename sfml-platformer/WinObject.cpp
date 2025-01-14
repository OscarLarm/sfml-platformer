#include "WinObject.h"

WinObject::WinObject()
	: win(false)
{
	setGameObject("portalSheet.png", sf::IntRect(0, 0, 32, 32), sf::Vector2f(32, 32));
	this->sprite.setScale(1.75f, 1.75f);
	this->hitBox.setScale(1.0f, 1.75f);
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
	updateAnimation(time, "portal");

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
