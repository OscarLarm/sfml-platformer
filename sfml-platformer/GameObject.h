#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.h"

class GameObject : public sf::Drawable
{
protected:



private:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	sf::RectangleShape hitBox;

	Animation* animationPtr;
	
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::RectangleShape getHitBox() const;
	virtual bool getWin() const;

	void setPosition(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
	virtual void setWin(bool win);

	void setGameObject(std::string textureFileName, sf::IntRect spriteRect, sf::Vector2f hitBoxSize);
	void updateAnimation(sf::Time time, std::string currentState, sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f));

	void setHitBoxSize(sf::Vector2f size);
	void setHitBoxOrigin(sf::Vector2f position);
	void setHitBoxScale(sf::Vector2f scale); // kanske flip
	void setHitBoxPosition(sf::Vector2f position);


	void setSpriteScale(sf::Vector2f scale);
	void setSpritePosition(sf::Vector2f position);

};

#endif // !GAMEOBJECT_H
