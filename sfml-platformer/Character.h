#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Platform.h"

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

	virtual void collisionControl(const std::vector<Platform>& platforms, const sf::Time& time) = 0;
	void collisionPlatform(const sf::FloatRect& hitBoxBounds, const sf::FloatRect& platformBounds);

private:


public:
	Character();
	~Character();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(const sf::Time& time, const std::vector<Platform>& platforms) = 0;

	void move(const sf::Vector2f offset);

	sf::Vector2f getVelocity() const;
};

#endif // !CHARACTER_H
