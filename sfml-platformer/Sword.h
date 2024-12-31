#ifndef SWORD_H
#define SWORD_H

#include "GameObject.h"

class Sword : public GameObject
{
private:
	bool lastFacingDirection;
	bool attacking;
	float attackDuration;
	float attackTimer;

public:
	Sword();
	~Sword();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::Time& time, const bool facingRight); // Make it override a virtual function. Possibly move virtual update from character to GameObjects

	void attack();
	void stopAttack();

	bool isAttacking() const;
};

#endif // !SWORD_H
