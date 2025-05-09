#include "Hud.h"

Hud::Hud()
	: totTimeStr("na"),
	playerLivesStr("na")
{
	if (!font.loadFromFile("../assets/GravityRegular5.ttf"))
	{
		std::cout << "Error loading font." << std::endl;
	}
	livesText.setFont(font);
	livesText.setString("HP!");
	livesText.setCharacterSize(15);
	livesText.setFillColor(sf::Color::White);

	timerText.setFont(font);
	timerText.setString("Timer!");
	timerText.setCharacterSize(15);
	timerText.setFillColor(sf::Color::White);
}

Hud::~Hud()
{
}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->livesText);
	target.draw(this->timerText);
}

void Hud::update(const float timer, const int lives, const sf::View& gameView)
{
	this->playerLivesStr = std::to_string(lives);
	totTimeStr = std::to_string(static_cast<int>(timer));
	livesText.setString("HP: " + playerLivesStr);
	timerText.setString("Time: " + totTimeStr);
	
	livesText.setPosition(gameView.getCenter().x + gameView.getSize().x / 2.5f - this->livesText.getGlobalBounds().width, gameView.getCenter().y - gameView.getSize().y / 2.5f);
	timerText.setPosition(gameView.getCenter().x - gameView.getSize().x / 2.5f, gameView.getCenter().y - gameView.getSize().y / 2.5f);
}
