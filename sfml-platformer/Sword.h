#ifndef SWORD_H
#define SWORD_H

#include "GameObject.h"
#include "Enemy.h"

class Sword : public GameObject
{
private:
	bool lastFacingRight;
	bool attacking;
	const float ATTACK_DURATION = 0.25f;
	float attackTimer;
	const int DAMAGE = 1;

public:
	Sword();
	~Sword();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::Time& time, const bool facingRight, std::vector<std::unique_ptr<GameObject>>& gameObjects);

	void attack();

	bool isAttacking() const;
};

#endif // !SWORD_H
