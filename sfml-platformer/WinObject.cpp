#include "WinObject.h"

WinObject::WinObject()
	: win(false)
{
	setGameObjectValues("portalSheet.png", sf::IntRect(0, 0, 32, 32), sf::Vector2f(32, 32));
	this->setSpriteScale(sf::Vector2f(1.75f, 1.75f));
	this->setHitBoxScale(sf::Vector2f(1.0f, 1.75f));

	setCurrentState(Animation::States::Portal);
}

WinObject::~WinObject()
{
}

void WinObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->getSprite());
	target.draw(this->getHitBox());
}

bool WinObject::update(const sf::Time& time)
{
	updateAnimation(time, getCurrentState());

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
