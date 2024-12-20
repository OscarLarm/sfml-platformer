#include "Player.h"
#include <iostream>

Player::Player() : moveSpeed(200.0f)
{
	this->texture.loadFromFile("../assets/player.png");
	this->sprite.setTexture(this->texture);
	this->setPosition(sf::Vector2f(50.0f, 600.0f));
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void Player::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));
}

sf::Vector2f Player::getPosition() const // FOR DEBUGGING
{
	return this->sprite.getPosition();
}

void Player::controller(const sf::Time& time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite.move(sf::Vector2f(moveSpeed * time.asSeconds(), 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sprite.move(sf::Vector2f(-moveSpeed * time.asSeconds(), 0));
	}
}
