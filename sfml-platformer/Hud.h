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

	const Player* playerPtr;
	std::string playerLivesStr;

	std::string totalTimeStr;

public:
	Hud(Player* player);
	~Hud();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(float timer);
};

#endif // !HUD_H
