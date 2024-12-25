#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
private:
	sf::IntRect spriteRect;
	float animationTimer;

	std::string previousState;

	int numOfFrames;
	int spriteRow;
	float animationSpeed;

	void idleAnimation();
	void runningAnimation();
	void jumpAnimation(float yVelocity);

public:
	Animation(sf::IntRect spriteRect);
	~Animation();
	sf::IntRect updateAnimation(const std::string& currentState, sf::Vector2f velocity, float timeAsSeconds);

};
#endif // !ANIMATOR_H
