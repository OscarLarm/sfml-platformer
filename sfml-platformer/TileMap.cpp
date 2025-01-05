#include "TileMap.h"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileMapTexture;

	target.draw(tileMap, states);
}

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::load(const int* level)
{
	if (!tileMapTexture.loadFromFile(TILE_MAP_PATH))
	{
		std::cout << "Couldn't load the Tilemap texture from path: " << TILE_MAP_PATH << std::endl;
	}

	tileMap.setPrimitiveType(sf::Triangles);
	tileMap.resize(20.0f * 10.0f * 6);

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			const int numOfTiles = level[i + j * 20];

			// TODO: include filesystem, using path for texture image.
			const int tileX = numOfTiles % (512 /*texture image width*/ / 32 /*tile width*/);
			const int tileY = numOfTiles / (512 /*texture image width*/ / 32 /*tile width*/);

			sf::Vertex* triangles = &tileMap[(i + j * 20) * 6];

			triangles[0].position = sf::Vector2f(i * 32, j * 32);
			triangles[1].position = sf::Vector2f((i + 1) * 32, j * 32);
			triangles[2].position = sf::Vector2f(i * 32, (j + 1) * 32);
			triangles[3].position = sf::Vector2f(i * 32, (j + 1) * 32);
			triangles[4].position = sf::Vector2f((i + 1) * 32, j * 32);
			triangles[5].position = sf::Vector2f((i + 1) * 32, (j + 1) * 32);



			//triangles[0].texCoords = sf::Vector2f(tileX * 32, tileY * 32);
			//triangles[1].texCoords = sf::Vector2f((tileX + 1) * 32, tileY * 32);
			//triangles[2].texCoords = sf::Vector2f(tileX * 32, (tileY + 1) * 32);
			//triangles[3].texCoords = sf::Vector2f(tileX * 32, (tileY + 1) * 32);
			//triangles[4].texCoords = sf::Vector2f((tileX + 1) * 32, tileY * 32);
			//triangles[5].texCoords = sf::Vector2f((tileX + 1)* 32, (tileY + 1) * 32);

		}
	}
}
