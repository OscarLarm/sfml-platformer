#include "Hud.h"
#include <iostream>

Hud::Hud(Player* player)
	: playerPtr(player),
	totalTimeStr("na"),
	playerLivesStr("na")
{
	if (!font.loadFromFile("../assets/GravityRegular5.ttf"))
	{
		std::cout << "Error loading font." << std::endl;
	}
	livesText.setFont(font);
	livesText.setString("HP!");
	livesText.setCharacterSize(25);
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(200, 50);

	timerText.setFont(font);
	timerText.setString("Timer!");
	timerText.setCharacterSize(25);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(550, 50);
}

Hud::~Hud()
{
}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->livesText);
	target.draw(this->timerText);
}

void Hud::update(float timer)
{
	this->playerLivesStr = std::to_string(playerPtr->getLives());

	totalTimeStr = std::to_string(static_cast<int>(timer));
	

	livesText.setString("HP: " + playerLivesStr);
	timerText.setString("Time: " + totalTimeStr);
}
