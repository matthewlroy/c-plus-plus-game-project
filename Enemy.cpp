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
Enemy::Enemy()
	:rectangle(sf::Vector2f(25.0f, 100.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, moveSpeed(250.0f)
	, velocity(0.0f, 0.0f)
	, active(true)
	, enemyFacing()
{
	rectangle.setFillColor(transparent_cyan);
}
Enemy::Enemy(sf::Vector2f position)
	:rectangle(sf::Vector2f(27.0f, 96.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, moveSpeed(250.0f)
	, velocity(0.0f, 0.0f)
	, active(true)
	, enemyFacing()
	, enemyBullet_clock(), enemyBullet_timer(), ENEMY_BULLET_SHOOT_DELAY(1.5f)
{
	//rectangle.setFillColor(transparent_cyan);
	rectangle.setPosition(position);
}

/* FUNCTIONS */
void Enemy::update(sf::Time deltaTime)
{
	//Enemy's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//update Enemy's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;

	//bullet clock
	enemyBullet_timer = enemyBullet_clock.getElapsedTime();
	//std::cout << enemyBullet_timer.asSeconds() << std::endl;

	rectangle.move(velocity * deltaTime.asSeconds());
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

/* DECONSTRUCTORS */
Enemy::~Enemy()
{
}
