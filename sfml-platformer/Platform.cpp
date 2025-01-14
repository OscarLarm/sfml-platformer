#include "Platform.h"

Platform::Platform() 
{
	setGameObject("tileSheet.png", sf::IntRect(0, 0, 48, 16), sf::Vector2f(48.0f, 16.0f));
}

Platform::~Platform()
{
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->getSprite());
	target.draw(this->getHitBox());
}

