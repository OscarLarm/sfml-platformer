#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Platform : public GameObject
{
private:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	sf::RectangleShape hitBox;


public:
	Platform();
	~Platform();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite getSprite() const;
	
	void setPosition(sf::Vector2f position);

};

#endif // !PLATFORM_H


//texture.setrepeated