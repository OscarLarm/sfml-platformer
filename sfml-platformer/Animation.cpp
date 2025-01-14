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

sf::IntRect Animation::update(float timeAsSeconds, States currentState, sf::Vector2f velocity)
{
	if (currentState != animationFrame.previousState || currentState == Animation::States::Jumping)
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
			//previousState = currentState;
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
			//animationFrame.previousState = currentState;
		}
	}
	return spriteRect;
}

void Animation::setFrameData(Animation::States state, sf::Vector2f velocity)
{
	switch (state)
	{
	case Animation::States::None:
		animationFrame = { 0,0,0.0f,Animation::States::None };
		break;
	case Animation::States::Idle:
		animationFrame = { 7,1,0.09f,Animation::States::Idle };
		break;
	case Animation::States::Running:
		animationFrame = { 8,3,0.06f,Animation::States::Running };
		break;
	case Animation::States::Jumping:
		animationFrame = { 1, 15, 0.01f, Animation::States::Jumping };

		if (velocity.y >= -40.0f && velocity.y <= 60.0f)
			animationFrame.row = 16;
		else if (velocity.y > 60.0f)
			animationFrame.row = 17;
		
		break;
	case Animation::States::IdleAttack:
		animationFrame = { 8,9,0.04f,Animation::States::IdleAttack };
		break;
	case Animation::States::RunningAttack:
		animationFrame = { 4,8,0.06f,Animation::States::RunningAttack };
		break;
	case Animation::States::JumpingAttack:
		animationFrame = { 4,18,0.06f,Animation::States::JumpingAttack };
		break;
	case Animation::States::Patrol:
		animationFrame = { 8,2,0.1f,Animation::States::Patrol };
		break;
	case Animation::States::Portal:
		animationFrame = { 3, 1, 0.1f, Animation::States::Portal };
		break;
	default:
		break;
	}
}

Animation::Animation(sf::IntRect spriteRect)
	: spriteRect(spriteRect),
	animationTimer(0.0f)
{
	animationFrame = {0,0,0.0f,Animation::States::None};
}

Animation::~Animation()
{
}
