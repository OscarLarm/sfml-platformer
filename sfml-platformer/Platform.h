#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Platform : public GameObject
{
private:

public:
	Platform();
	virtual ~Platform();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // !PLATFORM_H
