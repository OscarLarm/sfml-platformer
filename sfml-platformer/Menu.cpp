#include "Menu.h"

Menu::Menu(const sf::Vector2i& windowSize)
	: windowSize(windowSize),
	mainText("", fontBold, 32),
	secondaryText("", fontNormal, 20),
	choiceText("", fontNormal, 10)
{
	this->fontNormal.loadFromFile(NORMAL_FONT_PATH);
	this->fontBold.loadFromFile(BOLD_FONT_PATH);
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->mainText);
	target.draw(this->secondaryText);
	target.draw(this->choiceText);
}

void Menu::updateMenuText(const std::string& mainText, const std::string& secondaryText, const std::string& choice1, const std::string& choice2)
{
	this->mainText.setString(mainText);
	this->secondaryText.setString(secondaryText);
	this->choiceText.setString("- Press 'Enter' to " + choice1 + "\n\n\n\n- Press 'ESC' to " + choice2);

	this->mainText.setOrigin(this->mainText.getGlobalBounds().width / 2, this->mainText.getGlobalBounds().height / 2);
	this->mainText.setPosition(this->windowSize.x / 2.0f, this->windowSize.y / 3.5f);
	this->mainText.setFillColor(sf::Color::White);

	this->secondaryText.setOrigin(this->secondaryText.getGlobalBounds().width / 2, this->secondaryText.getGlobalBounds().height / 2);
	this->secondaryText.setPosition(this->windowSize.x / 2.0f, this->windowSize.y / 2.5f);
	this->secondaryText.setFillColor(sf::Color::White);

	this->choiceText.setFillColor(sf::Color::White);
	this->choiceText.setOrigin(this->choiceText.getGlobalBounds().width / 2, this->choiceText.getGlobalBounds().height / 2);
	this->choiceText.setPosition(this->windowSize.x / 2.0f, this->windowSize.y / 1.5f);
}
