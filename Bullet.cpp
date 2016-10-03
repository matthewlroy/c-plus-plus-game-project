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
Bullet::Bullet()
	:rectangle(sf::Vector2f(10.0f, 10.0f))
	, velocity(0.0f, 0.0f), moveSpeed(800.0f)
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, clock(), timer()
	, active(true)
	, BULLET_LIFESPAN(1.5f)
{
	rectangle.setFillColor(transparent_red);
}
Bullet::Bullet(sf::Vector2f position)
	:rectangle(sf::Vector2f(10.0f, 10.0f))
	, velocity(0.0f, 0.0f), moveSpeed(800.0f)
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, clock(), timer()
	, active(true)
	, BULLET_LIFESPAN(1.5f)
{
	rectangle.setFillColor(transparent_red);
	rectangle.setPosition(position);
}
Bullet::Bullet(sf::Vector2f position, sf::Vector2f bVelocity)
	:rectangle(sf::Vector2f(8.0f, 8.0f))
	, velocity(bVelocity), moveSpeed(1800.0f)
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, clock(), timer()
	, active(true)
	, BULLET_LIFESPAN(0.55f)
{
	//rectangle.setFillColor(transparent_red);
	rectangle.setPosition(position);
}

/* FUNCTIONS */
void Bullet::update(sf::Time deltaTime)
{
	//Bullet's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//update Bullet's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;

	//move bullet
	rectangle.move(velocity * moveSpeed * deltaTime.asSeconds());

	//remove bullets
	timer = clock.getElapsedTime();
	if (timer.asSeconds() > BULLET_LIFESPAN)
	{
		clock.restart();
		active = false;
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

/* DECONSTRUCTORS */
Bullet::~Bullet()
{
}
