#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	const std::string TILE_MAP_PATH = "../assets/tileSheet.png";

	sf::VertexArray tileMap;
	sf::Texture tileMapTexture;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


public:
	TileMap();
	~TileMap();

	void load(const int* level);
};

#endif // !TILEMAP_H
