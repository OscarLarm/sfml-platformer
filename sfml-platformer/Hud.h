#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Hud : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text livesText;
	sf::Text timerText;

	std::string playerLivesStr;

	std::string totTimeStr;
	
public:
	Hud();
	virtual ~Hud();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const float timer, const int lives, const sf::View& gameView);
};

#endif // !HUD_H
