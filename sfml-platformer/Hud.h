#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

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
	void update(float totTime, Player* player, sf::View& gameView);
};

#endif // !HUD_H
