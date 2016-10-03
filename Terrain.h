#pragma once
enum TerrainType { Ground, Platform, JumpPlatform, Bridge, AGPlatform };
class Terrain
{
public:
	Terrain();
	Terrain(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	Terrain(sf::Vector2f size, sf::Vector2f position, sf::Color color, TerrainType tTerrainType);
	Terrain(sf::Vector2f size, sf::Vector2f position, TerrainType tTerrainType);
	
	void update(sf::Time deltaTime);
	float top, left, right, bottom;

	void draw(sf::RenderWindow& window);

	sf::RectangleShape rectangle;

	TerrainType terrainType;

	~Terrain();
};

