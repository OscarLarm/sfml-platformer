#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
private:
	int windowWidth;
	int windowHeight;
	sf::RenderWindow window;

public:
	Game(int windowWidth = 900, int windowHeight = 600);
	~Game();
	void start();
	void end();
};

#endif // !GAME_H
