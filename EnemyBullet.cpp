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
EnemyBullet::EnemyBullet()
	:rectangle(sf::Vector2f(19.0f, 6.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, active(true)
	, clock(), timer()
	, BULLET_LIFESPAN(3.0f)
	, velocity(0.0f, 0.0f), moveSpeed(300.0f)
{
}

EnemyBullet::EnemyBullet(sf::Vector2f position)
	:rectangle(sf::Vector2f(19.0f, 6.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, active(true)
	, clock(), timer()
	, BULLET_LIFESPAN(3.0f)
	, velocity(0.0f, 0.0f), moveSpeed(300.0f)
{
	rectangle.setPosition(position);
}

EnemyBullet::EnemyBullet(sf::Vector2f position, sf::Vector2f velocity)
	:rectangle(sf::Vector2f(19.0f, 6.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, active(true)
	, clock(), timer()
	, BULLET_LIFESPAN(3.0f)
	, velocity(0.0f, 0.0f), moveSpeed(300.0f)
{
	rectangle.setPosition(position);
}

/* FUNCTIONS */
void EnemyBullet::update(sf::Time deltaTime)
{
	//EnemyBullet's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//EnemyBullet Bullet's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;

	//move bullets
	rectangle.move(velocity * deltaTime.asSeconds());

	//remove bullets
	timer = clock.getElapsedTime();
	if (timer.asSeconds() > BULLET_LIFESPAN)
	{
		clock.restart();
		active = false;
	}
}

void EnemyBullet::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

/* DECONSTRUCTORS */
EnemyBullet::~EnemyBullet()
{
}
