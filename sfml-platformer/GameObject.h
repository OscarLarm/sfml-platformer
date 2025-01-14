#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.h"

class GameObject : public sf::Drawable
{
private:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	sf::RectangleShape hitBox;

	Animation* animationPtr;
	Animation::States currentState;

protected:
	void updateAnimation(const sf::Time& time, const Animation::States currentState, const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f));

	sf::Sprite getSprite() const;
	Animation::States getCurrentState() const;


	void setGameObjectValues(const std::string& textureFileName, const sf::IntRect& spriteRect, const sf::Vector2f& hitBoxSize);
	void setHitBoxSize(const sf::Vector2f& size);
	void setHitBoxOrigin(const sf::Vector2f& position);
	void setHitBoxScale(const sf::Vector2f& scale);
	void setHitBoxPosition(const sf::Vector2f& position);

	void setSpriteScale(const sf::Vector2f& scale);
	void setSpritePosition(const sf::Vector2f& position);

	void setCurrentState(const Animation::States state);

	
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	sf::Vector2f getPosition() const;
	sf::RectangleShape getHitBox() const;
	virtual bool getWin() const;

	void setPosition(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
	virtual void setWin(const bool win);
};

#endif // !GAMEOBJECT_H
