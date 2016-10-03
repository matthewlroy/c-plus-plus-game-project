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
Weapon::Weapon()
	:rectangle()
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, gun_tex(), rifle_tex()
{
}

/* FUNCTIONS */
void Weapon::create(const std::string& path)
{
	//rectangle.setFillColor(transparent_magenta);

	if (!gun_tex.loadFromFile("Data/Textures/gun.png")) std::cout << "ERROR: Weapon::create could not load 'gun_tex'...\n";
	if (!rifle_tex.loadFromFile("Data/Textures/rifle.png")) std::cout << "ERROR: Weapon::create could not load 'rifle_tex'...\n";
}

void Weapon::update(sf::Time deltaTime)
{
	if (weaponCurrentWeapon == Gun)
	{
		rectangle.setSize(sf::Vector2f(18.0f, 13.0f));
		rectangle.setTextureRect(sf::IntRect(0, 0, 18, 13));
		rectangle.setTexture(&gun_tex);
	}
	else if (weaponCurrentWeapon == Rifle)
	{
		rectangle.setSize(sf::Vector2f(26.0f, 16.0f));
		rectangle.setTextureRect(sf::IntRect(0, 0, 26, 16));
		rectangle.setTexture(&rifle_tex);
	}

	//Weapon's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//update Weapon's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;
}

void Weapon::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

/* DECONSTRUCTORS */
Weapon::~Weapon()
{
}
