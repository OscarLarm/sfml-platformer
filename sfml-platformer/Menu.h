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

public:
	Menu(const sf::Vector2i& windowSize, const std::string& mainText, const std::string& secondaryText, const std::string& choice1, const std::string& choice2);
	~Menu();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateMenuText(const std::string& mainText, const std::string& secondaryText, const std::string& choice1, const std::string& choice2);
};

#endif // !MENU_H
