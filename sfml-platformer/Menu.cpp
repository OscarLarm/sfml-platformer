#include "Menu.h"
#include <iostream>

Menu::Menu(const sf::Vector2i& windowSize, const std::string& mainText, const std::string& secondaryText, const std::string& choiceText)
	: windowSize(windowSize),
	mainText(mainText, fontBold, 32),
	secondaryText(secondaryText, fontNormal, 20),
	choiceText(choiceText, fontNormal, 10),
	menuState(0)
{
	this->fontNormal.loadFromFile("../assets/GravityRegular5.ttf");
	this->fontBold.loadFromFile("../assets/GravityBold8.ttf");
	
	this->mainText.setOrigin(this->mainText.getGlobalBounds().width / 2, this->mainText.getGlobalBounds().height / 2);
	this->mainText.setFillColor(sf::Color::White);
	this->mainText.setPosition(this->windowSize.x / 2.0f, this->windowSize.y / 3.5f);

	this->secondaryText.setOrigin(this->secondaryText.getGlobalBounds().width / 2, this->secondaryText.getGlobalBounds().height / 2);
	this->secondaryText.setFillColor(sf::Color::White);
	this->secondaryText.setPosition(this->windowSize.x / 2.0f, this->windowSize.y / 2.5f);

	this->choiceText.setOrigin(this->choiceText.getGlobalBounds().width / 2, this->choiceText.getGlobalBounds().height / 2);
	this->choiceText.setFillColor(sf::Color::White);
	this->choiceText.setPosition(this->windowSize.x / 2.0f, this->windowSize.y / 1.5f);
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

void Menu::setText(const std::string& mainText, const std::string& secondaryText, const std::string& choiceText)
{
}

int Menu::update()
{
	return this->menuState;
}

void Menu::setMenuState(const sf::Event& event)
{
	//std::cout << event.KeyPressed << std::endl;
	if (event.key.code == sf::Keyboard::Enter)
	{
		this->menuState = 1;
	}
	else if (event.key.code == sf::Keyboard::Escape)
	{
		this->menuState = 5;
	}
}
