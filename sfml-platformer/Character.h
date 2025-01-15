#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Platform.h"
#include <vector>
#include <iostream>

class Character : public GameObject
{
private:
	const float GRAVITY = 900.0f;
	float moveSpeed;
	sf::Vector2f velocity;
	bool grounded;
	bool facingRight;
	int lives;
	int startLives;

	bool alive;
	bool gotHit;
	sf::Vector2f startPosition;

protected:
	virtual void collisionControl(const sf::Time& time, std::vector<std::unique_ptr<GameObject>>& gameObjects) = 0;
	void collisionPlatform(const sf::FloatRect& hitBoxBounds, const sf::FloatRect& platformBounds);
	void move(const sf::Vector2f& offset);
	void flip();

	float getMoveSpeed() const;
	float getGravity() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getStartPosition() const;
	bool isGrounded() const;
	bool isFacingRight() const;

	void setCharacterValues(const int lives, const float moveSpeed);
	void setVelocity(const float x, const float y);
	void setStartPosition(const sf::Vector2f& position);
	void setGrounded(const bool grounded);
	void setAlive(const bool alive);

public:
	Character();
	virtual ~Character();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(const sf::Time& time, std::vector<std::unique_ptr<GameObject>>& gameObjects) = 0;

	virtual void resetPosition();
	virtual void resetLives();

	virtual void hit(const int damage = 1);

	virtual int getLives() const;
	virtual bool isAlive() const;
	virtual bool isHit() const;
	
	void setHit(bool hit);
};

#endif // !CHARACTER_H
