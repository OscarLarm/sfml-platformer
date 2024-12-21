#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float moveSpeed;

public:
	Player();
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	void setPosition(const sf::Vector2f& position);

	sf::Vector2f getPosition() const; // FOR DEBUGGING

	sf::Sprite getSprite() const;
	
	void controller(const sf::Time& time);



	//// FOR TESTING
	//sf::RectangleShape border;
};

#endif // !PLAYER_H
