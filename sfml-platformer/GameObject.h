#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class GameObject : public sf::Drawable
{
protected:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	sf::RectangleShape hitBox;

private:
	
public:
	GameObject();
	~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::RectangleShape getHitBox() const;
	virtual bool getWin() const;

	void setPosition(const sf::Vector2f& position);
	virtual void setWin(bool win);
};

#endif // !GAMEOBJECT_H
