#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

class Platform : public sf::Drawable//: public GameObject
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;

public:
	//sf::VertexArray platforms

	Platform(sf::Vector2f position = sf::Vector2f(0.0f,0.0f));
	~Platform();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	void setPosition(const sf::Vector2f& position);

	sf::Sprite getSprite() const;

};

#endif // !PLATFORM_H


//texture.setrepeated