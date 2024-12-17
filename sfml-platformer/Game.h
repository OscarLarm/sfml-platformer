#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
private:
	int windowWidth;
	int windowHeight;

	sf::RenderWindow window;
	

	void eventHandler();	
	void update();
	void render();

public:
	Game();
	~Game();
	void start();
};

#endif // !GAME_H
