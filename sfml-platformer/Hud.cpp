#include "Hud.h"
#include <iostream>

Hud::Hud(Player*& player)
	: player(player),
	totalTime(0.0f),
	totalTimeStr("na"),
	playerLivesStr("na")
{
	if (!font.loadFromFile("../assets/GravityRegular5.ttf"))
	{
		std::cout << "Error loading font." << std::endl;
	}
	lives.setFont(font);
	lives.setString("HP!");
	lives.setCharacterSize(25);
	lives.setFillColor(sf::Color::White);
	lives.setPosition(200, 50);

	timer.setFont(font);
	timer.setString("Timer!");
	timer.setCharacterSize(25);
	timer.setFillColor(sf::Color::White);
	timer.setPosition(550, 50);
}

Hud::~Hud()
{
}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->lives);
	target.draw(this->timer);
}

void Hud::update(const sf::Time& time)
{
	this->playerLivesStr = std::to_string(player->getLives());

	totalTime += time.asSeconds();
	totalTimeStr = std::to_string(static_cast<int>(totalTime));
	

	lives.setString("HP: " + playerLivesStr);
	timer.setString("Time: " + totalTimeStr);
}
