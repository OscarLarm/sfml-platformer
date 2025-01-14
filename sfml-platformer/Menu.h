#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Menu : public sf::Drawable
{
private:
	const std::string NORMAL_FONT_PATH = "../assets/GravityRegular5.ttf";
	const std::string BOLD_FONT_PATH = "../assets/GravityBold8.ttf";

	sf::Vector2i windowSize;

	sf::Font fontNormal;
	sf::Font fontBold;

	sf::Text mainText;
	sf::Text secondaryText;
	sf::Text choiceText;

public:
	Menu(const sf::Vector2i& windowSize);
	virtual ~Menu();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateMenuText(const std::string& mainText, const std::string& secondaryText, const std::string& choice1, const std::string& choice2);
};

#endif // !MENU_H
