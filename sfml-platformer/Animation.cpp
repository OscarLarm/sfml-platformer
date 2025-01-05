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
	animationSpeed = 0.07f;
}

void Animation::patrolAnimation()
{
	numOfFrames = 8;
	spriteRow = 2;
	animationSpeed = 0.1f;
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

void Animation::jumpAttackAnimation()
{
	numOfFrames = 4;
	spriteRow = 18;
	animationSpeed = 0.06f;
}

void Animation::idleAttackAnimation()
{
	numOfFrames = 8;
	spriteRow = 9;
	animationSpeed = 0.04f;
}

void Animation::runningAttackAnimation()
{
	numOfFrames = 4;
	spriteRow = 8;
	animationSpeed = 0.06f;
}

void Animation::portalAnimation()
{
	numOfFrames = 3;
	animationSpeed = 0.1f;

	if (spriteRect.left == spriteRect.width * (numOfFrames - 1))
	{
		spriteRect.left = 0;
		if (spriteRect.top == 0)
		{
			spriteRect.top = spriteRect.height;
		}
		else if (spriteRect.top == 32)
		{
			spriteRect.top = 0;
		}
	}
	else
	{
		spriteRect.left += spriteRect.width;
	}
}



sf::IntRect Animation::updateAnimation(float timeAsSeconds, const std::string& currentState, sf::Vector2f velocity)
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
	else if (currentState == "patrol")
	{
		patrolAnimation();
	}
	else if (currentState == "jumping-attack")
	{
		jumpAttackAnimation();
	}
	else if (currentState == "idle-attack")
	{
		idleAttackAnimation();
	}
	else if (currentState == "running-attack")
	{
		runningAttackAnimation();
	}
	else if (currentState == "portal")
	{
		animationTimer += timeAsSeconds;
		if (animationTimer >= animationSpeed)
		{
			portalAnimation();
			animationTimer = 0.0f;
			previousState = currentState;
		}
		return spriteRect;
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
