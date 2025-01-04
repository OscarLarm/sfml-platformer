#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

class Menu : public sf::Drawable
{
private:
	sf::Vector2i windowSize;

	sf::Font fontNormal;
	sf::Font fontBold;

	sf::Text mainText;
	sf::Text secondaryText;
	sf::Text choiceText;

	int menuState;

public:
	Menu(const sf::Vector2i& windowSize, const std::string& mainText, const std::string& secondaryText, const std::string& choiceText);
	~Menu();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setText(const std::string& mainText, const std::string& secondaryText, const std::string& choiceText);
	int update();
	void setMenuState(const sf::Event& event);
};

#endif // !MENU_H
