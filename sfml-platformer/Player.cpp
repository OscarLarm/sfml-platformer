#include "Player.h"
#include <iostream>

Player::Player() : moveSpeed(200.0f)
{
	this->texture.loadFromFile("../assets/playerSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 96, 84));
	this->setPosition(sf::Vector2f(50.0f, 600.0f));

	//// for testing 
	//sf::FloatRect bounds = this->sprite.getGlobalBounds();
	//this->border.setSize(sf::Vector2f(bounds.width, bounds.height));
	//this->border.setPosition(bounds.left, bounds.top);
	//this->border.setOutlineColor(sf::Color::Red);
	//this->border.setFillColor(sf::Color::Transparent);
	//this->border.setOutlineThickness(1.0f);
	//std::cout << bounds.getSize().x << ", " << bounds.getSize().y << std::endl;
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	
	//// FOR TESTING
	//target.draw(this->border);
}

void Player::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
	
}

sf::Vector2f Player::getPosition() const // FOR DEBUGGING
{
	return this->sprite.getPosition();
}

sf::Sprite Player::getSprite() const
{
	return this->sprite;
}

void Player::controller(const sf::Time& time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->sprite.move(sf::Vector2f(moveSpeed * time.asSeconds(), 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->sprite.move(sf::Vector2f(-moveSpeed * time.asSeconds(), 0));
	}

	// y movement for testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->sprite.move(sf::Vector2f(0, moveSpeed * time.asSeconds()));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->sprite.move(sf::Vector2f(0, -moveSpeed * time.asSeconds()));
	}
}
