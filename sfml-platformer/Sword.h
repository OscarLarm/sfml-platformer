#ifndef SWORD_H
#define SWORD_H

#include "GameObject.h"
#include "Enemy.h"

class Sword : public GameObject
{
private:
	bool lastFacingDirection;
	bool attacking;
	float attackDuration;
	float attackTimer;
	int damage;

public:
	Sword();
	~Sword();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::Time& time, const bool facingRight, std::vector<GameObject*>& gameObjects); // Make it override a virtual function. Possibly move virtual update from character to GameObjects

	void attack();
	void stopAttack();

	bool isAttacking() const;
};

#endif // !SWORD_H
