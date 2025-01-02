#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

class Hud : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text lives;
	sf::Text timer;

	const Player* player;
	std::string playerLivesStr;

	float totalTime;
	std::string totalTimeStr;


public:
	Hud(Player*& player);
	~Hud();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::Time& time);
};

#endif // !HUD_H
