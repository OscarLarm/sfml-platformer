#include "Player.h"
#include <iostream>

Player::Player() : moveSpeed(200.0f)
{
	this->texture.loadFromFile("../assets/playerSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 96, 84));
	this->setPosition(sf::Vector2f(50.0f, 400.0f));

	this->velocity = sf::Vector2f(0.0f, 0.0f);
	this->grounded = false;

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
	//// Movement using move instead of velocity
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//{
	//	this->sprite.move(sf::Vector2f(moveSpeed * time.asSeconds(), 0));
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//{
	//	this->sprite.move(sf::Vector2f(-moveSpeed * time.asSeconds(), 0));
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//{
	//	this->jump(time);
	//}

	if (!this->grounded)
	{
		this->velocity.y += gravity * time.asSeconds();
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && 
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		this->velocity.x = this->moveSpeed;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
		!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		this->velocity.x = - this->moveSpeed;
	}
	else
	{
		this->velocity.x = 0;
	}

	this->sprite.move(velocity * time.asSeconds());


	// Collision for window borders
	// TODO: Change collision to check for sprite intersect.
	if (this->getPosition().y >= 650.0f)
	{
		this->grounded = true;
		velocity.y = 0;
	}
	else
	{
		grounded = false;
	}
	std::cout << "Grounded: " << this->grounded << std::endl;
	if (this->getPosition().x <= 0.0f)
	{
		this->setPosition(sf::Vector2f(0.0f, this->getPosition().y));
		this->velocity.x = 0;
	}
	if (this->getPosition().x >= 1366.0f - this->getSprite().getGlobalBounds().width)
	{
		this->setPosition(sf::Vector2f(1366.0f - this->getSprite().getGlobalBounds().width, this->getPosition().y));
		this->velocity.x = 0;
	}
}

void Player::jump(const sf::Time& time)
{
	if (grounded)
	{
		this->velocity.y = this->jumpForce;
		this->grounded = false;
	}
}
