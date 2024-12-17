#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	GameObject();
	~GameObject();

	//void collision();
};

#endif // !GAMEOBJECT_H
