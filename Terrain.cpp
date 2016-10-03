/* LIBRARIES */
//cpp
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <xstring>
#include <sstream>
#include <string>

//sfml
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//headers
#include "Globals.h"
#include "Game.h"
#include "Terrain.h"
#include "Player.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "HUD.h"
#include "EnemyBullet.h"
#include "Upgrade.h"
#include "Menu.h"

/* CONSTRUCTORS */
Terrain::Terrain()
	:rectangle()
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, terrainType(Platform)
{
}
Terrain::Terrain(sf::Vector2f size, sf::Vector2f position, sf::Color color)
	:rectangle()
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, terrainType(Platform)
{
	rectangle.setSize(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
}
Terrain::Terrain(sf::Vector2f size, sf::Vector2f position, sf::Color color, TerrainType tTerrainType)
	:rectangle()
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, terrainType(tTerrainType)
{
	rectangle.setSize(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
}
Terrain::Terrain(sf::Vector2f size, sf::Vector2f position, TerrainType tTerrainType)
	:rectangle()
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, terrainType(tTerrainType)
{
	rectangle.setSize(size);
	rectangle.setPosition(position);
}

/* FUNCTIONS */
void Terrain::update(sf::Time deltaTime)
{
	//terrain collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + rectangle.getSize().x;
	bottom = rectangle.getPosition().y + rectangle.getSize().y;

	//if (terrainType == Ground) rectangle.setFillColor(transparent_blue);
	//if (terrainType == JumpPlatform) rectangle.setFillColor(transparent_red);
	//if (terrainType == Platform) rectangle.setFillColor(transparent_white);
}

void Terrain::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

/* DECONSTRUCTORS */
Terrain::~Terrain()
{
}
