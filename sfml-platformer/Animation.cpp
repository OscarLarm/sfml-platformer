#include "Animation.h"

void Animation::portalAnimation()
{
	if (spriteRect.left == spriteRect.width * (animationFrame.nrOfFrames - 1))
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

sf::IntRect Animation::update(const float timeAsSeconds, const States currentState, const sf::Vector2f& velocity)
{
	if (currentState != previousState || currentState == Animation::States::Jumping)
	{
		spriteRect.left = 0;
	}
	
	setFrameData(currentState, velocity);
	
	if (currentState == Animation::States::Portal)
	{
		animationTimer += timeAsSeconds;
		if (animationTimer >= animationFrame.speed)
		{
			portalAnimation();
			animationTimer = 0.0f;
		}
	}
	else
	{
		spriteRect.top = spriteRect.height * (animationFrame.row - 1);
		animationTimer += timeAsSeconds;

		if (animationTimer >= animationFrame.speed)
		{
			if (spriteRect.left == spriteRect.width * (animationFrame.nrOfFrames - 1))
			{
				spriteRect.left = 0;
			}
			else
			{
				spriteRect.left += spriteRect.width;
			}
			animationTimer = 0.0f;
		}
	}
	return spriteRect;
}

void Animation::setFrameData(const Animation::States& state, const sf::Vector2f& velocity)
{
	switch (state)
	{
	case Animation::States::None:
		animationFrame = { 0,0,0.0f };
		break;
	case Animation::States::Idle:
		animationFrame = { 7,1,0.09f };
		break;
	case Animation::States::Running:
		animationFrame = { 8,3,0.06f };
		break;
	case Animation::States::Jumping:
		animationFrame = { 1, 15, 0.01f };

		if (velocity.y >= -40.0f && velocity.y <= 60.0f)
			animationFrame.row = 16;
		else if (velocity.y > 60.0f)
			animationFrame.row = 17;
		
		break;
	case Animation::States::IdleAttack:
		animationFrame = { 8,9,0.04f };
		break;
	case Animation::States::RunningAttack:
		animationFrame = { 4,8,0.06f };
		break;
	case Animation::States::JumpingAttack:
		animationFrame = { 4,18,0.06f };
		break;
	case Animation::States::Patrol:
		animationFrame = { 8,2,0.1f };
		break;
	case Animation::States::Portal:
		animationFrame = { 3, 1, 0.1f };
		break;
	default:
		break;
	}
	previousState = state;
}

Animation::Animation(sf::IntRect spriteRect)
	: spriteRect(spriteRect),
	animationTimer(0.0f),
	previousState(States::None)
{
	animationFrame = { 0,0,0.0f };
}

Animation::~Animation()
{
}
