#ifndef WINOBJECT_H
#define WINOBJECT_H

#include "GameObject.h"
#include "Animation.h"

class WinObject : public GameObject
{
private:
	bool win;
	Animation* portalAnimation;

public:
	WinObject();
	~WinObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool update(sf::Time time);

	void setWin(bool win) override;
};

#endif // !WINOBJECT_H

