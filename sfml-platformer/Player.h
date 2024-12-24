#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
private:
	const std::string ASSETS_DIRECTORY = "../assets/";

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i size;

	float moveSpeed;
	sf::Vector2f velocity;

	float gravity = 900.0f;
	float jumpForce = -350.0f;
	bool grounded;

	float animationTimer;
	std::string currentState;
	std::string previousState;
	sf::IntRect animationFrame;
	void updateAnimation(sf::Time time);
	int numOfFrames;
	int row;
	float animationSpeed;
	bool facingRight;

public:
	Player();
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	void setPosition(const sf::Vector2f& position);

	sf::Vector2f getPosition() const; // FOR DEBUGGING

	sf::Sprite getSprite() const;
	
	void controller(const sf::Time& time);

	void jump(const sf::Time& time);

	//// FOR TESTING
	//sf::RectangleShape border;
};

#endif // !PLAYER_H
