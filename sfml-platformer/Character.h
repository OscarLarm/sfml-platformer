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


	void collision(const std::vector<Platform>& platforms, const sf::Time& time);

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
