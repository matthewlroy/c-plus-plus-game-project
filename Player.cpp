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
Player::Player()
	:rectangle(sf::Vector2f(46.0f, 102.0f))
	, velocity(0.0f, 0.0f)
	, moveSpeed(400.0f), jumpSpeed(750.0f)
	, isJumping(false)
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, bottomCollision(false), bottomCollisionLocation()
	, rightCollision(false), rightCollisionLocation()
	, leftCollision(false), leftCollisionLocation()
	, agCollision(false)
	, playerFacing(Right)
	, player_tex()
	, health(5), shieldDurability(0), rifleBullets(0)
	, shield(false), speed(false)
	, shield_tex(), shield_rect(sf::Vector2f(52.0f, 108.0f))
	, speed_tex(), speed_rect(sf::Vector2f(46.0f, 102.0f))
	, speedDuration_clock(), speedDuration_timer(), SPEED_DURATION(4.0f)
{
}

/* FUNCTIONS */
void Player::create(const std::string& path)
{
	//rectangle.setFillColor(transparent_green);
	rectangle.setPosition(100.0f, 100.0f);
	
	//player
	if (!player_tex.loadFromFile("Data/Textures/player.png")) std::cout << "ERROR: Player::create could not load 'player_tex'...\n";
	rectangle.setTexture(&player_tex);

	//shield
	if (!shield_tex.loadFromFile("Data/Textures/playershield.png")) std::cout << "ERROR: Player::create could not load 'shield_tex'...\n";
	shield_rect.setTexture(&shield_tex);

	//speed
	if (!speed_tex.loadFromFile("Data/Textures/playerspeed.png")) std::cout << "ERROR: Player::create could not load 'speed_tex'...\n";
	speed_rect.setTexture(&speed_tex);
}

void Player::update(sf::Time deltaTime)
{
	//player's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//update player's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;

	speedDuration_timer = speedDuration_clock.getElapsedTime();
	//std::cout << speedDuration_timer.asSeconds() << std::endl;

	if (speed && speedDuration_timer.asSeconds() >= SPEED_DURATION)
		speed = false;
}

void Player::resetSpeedDuration()
{
	speedDuration_clock.restart();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
	if (shield) window.draw(shield_rect);
	if (speed) window.draw(speed_rect);
}

/* DECONSTRUCTORS */
Player::~Player()
{
}
