#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Platform.h"
#include <vector>
#include <iostream>

class Character : public GameObject
{
private:
	float moveSpeed;
	sf::Vector2f velocity;
	float gravity;
	bool grounded;
	bool facingRight;
	int lives;
	int startLives;

	bool alive;
	bool gotHit;
	sf::Vector2f startPosition;

protected:
	virtual void collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects) = 0;
	void collisionPlatform(const sf::FloatRect& hitBoxBounds, const sf::FloatRect& platformBounds);
	void move(const sf::Vector2f offset);
	void flip();

	float getMoveSpeed() const;
	float getGravity() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getStartPosition() const;
	bool isGrounded() const;
	bool isFacingRight() const;

	void setCharacterValues(int lives, float moveSpeed);
	void setVelocity(float x, float y);
	void setStartPosition(const sf::Vector2f& position);
	void setGrounded(bool grounded);
	void setAlive(bool alive);

public:
	Character();
	virtual ~Character();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(const sf::Time& time, std::vector<GameObject*>& gameObjects) = 0;

	virtual void resetPosition();
	virtual void resetLives();

	virtual void hit(const int damage = 1);

	virtual int getLives() const;
	virtual bool isAlive() const;
	virtual bool isHit() const;
	
	void setHit(bool hit);
};

#endif // !CHARACTER_H
