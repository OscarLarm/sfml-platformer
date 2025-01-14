#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Platform.h"
#include <vector>
#include <iostream>

class Character : public GameObject
{
protected:
	float moveSpeed;
	sf::Vector2f velocity;
	float gravity;
	bool grounded;
	std::string state;
	bool facingRight;
	int lives;
	int startLives;


	bool alive;
	bool gotHit;

	virtual void collisionControl(const sf::Time& time, std::vector<GameObject*>& gameObjects) = 0;
	void collisionPlatform(const sf::FloatRect& hitBoxBounds, const sf::FloatRect& platformBounds);

	sf::Vector2f startPosition;

private:


public:
	Character();
	virtual ~Character();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(const sf::Time& time, std::vector<GameObject*>& gameObjects) = 0;

	void move(const sf::Vector2f offset);
	virtual void resetPosition();
	virtual void resetLives();
	virtual void hit(const int damage = 1);

	sf::Vector2f getVelocity() const;
	virtual int getLives() const;
	virtual bool isAlive() const;
	virtual bool isHit() const;

	void setStartPosition(const sf::Vector2f& position);

};

#endif // !CHARACTER_H
