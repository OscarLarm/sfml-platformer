#ifndef WINOBJECT_H
#define WINOBJECT_H

#include "GameObject.h"

class WinObject : public GameObject
{
private:
	bool win;

public:
	WinObject();
	virtual ~WinObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool update(const sf::Time& time);

	void setWin(const bool win) override;
};

#endif // !WINOBJECT_H

