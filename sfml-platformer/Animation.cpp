#include "Animation.h"

void Animation::idleAnimation()
{
	numOfFrames = 7;
	spriteRow = 1;
	animationSpeed = 0.09f;
}

void Animation::runningAnimation()
{
	numOfFrames = 8;
	spriteRow = 3;
	animationSpeed = 0.08f;
}

void Animation::jumpAnimation(float yVelocity)
{
	numOfFrames = 1;
	animationSpeed = 0.01f;
	spriteRow = 15;
	
	if (yVelocity >= -40.0f && yVelocity <= 60.0f)
	{
		spriteRow = 16;
	}
	else if (yVelocity > 60.0f)
	{
		spriteRow = 17;
	}
}

sf::IntRect Animation::updateAnimation(const std::string& currentState, sf::Vector2f velocity, float timeAsSeconds)
{
	if (currentState != previousState || currentState == "jumping")
	{
		spriteRect.left = 0;
	}

	if (currentState == "jumping")
	{
		jumpAnimation(velocity.y);
	}
	else if (currentState == "idle")
	{
		idleAnimation();
	}
	else if (currentState == "running")
	{
		runningAnimation();
	}

	spriteRect.top = spriteRect.height * (spriteRow - 1);
	animationTimer += timeAsSeconds;

	if (animationTimer >= animationSpeed)
	{
		if (spriteRect.left == spriteRect.width * (numOfFrames - 1))
		{
			spriteRect.left = 0;
		}
		else
		{
			spriteRect.left += spriteRect.width;
		}
		animationTimer = 0.0f;
		previousState = currentState;
	}
	return spriteRect;
}

Animation::Animation(sf::IntRect spriteRect)
	: spriteRect(spriteRect),
	animationTimer(0.0f),
	previousState("none"),
	numOfFrames(0),
	spriteRow(0),
	animationSpeed(0.0f)
{
}

Animation::~Animation()
{
}