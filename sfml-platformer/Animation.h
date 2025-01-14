#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
public:
	enum class States
	{
		None,
		Idle,
		Running,
		Jumping,
		IdleAttack,
		RunningAttack,
		JumpingAttack,
		Patrol,
		Portal
	};

private:
	sf::IntRect spriteRect;
	float animationTimer;
	
	void portalAnimation();

	struct AnimationFrames
	{
		int nrOfFrames;
		int row;
		float speed;
		Animation::States previousState;
	} animationFrame;

	void setFrameData(Animation::States state, sf::Vector2f velocity);

public:
	Animation(sf::IntRect spriteRect);
	virtual ~Animation();
	


	sf::IntRect update(float timeAsSeconds, States currentState, sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f));
};
#endif // !ANIMATION_H
