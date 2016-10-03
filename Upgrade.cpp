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
Upgrade::Upgrade()
	:rectangle(sf::Vector2f(46.0f, 46.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, velocity(0.0f, 0.0f), floatSpeed(25.0f)
	, floatHeight(1.25f)
	, active(true)
{
}
Upgrade::Upgrade(UpgradeType upType)
	:rectangle(sf::Vector2f(46.0f, 46.0f))
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, velocity(0.0f, 0.0f), floatSpeed(25.0f)
	, floatHeight(1.25f)
	, active(true)
	, upgradeType(upType)
{
	if (upgradeType == Health)
	{
		rectangle.setPosition(SCREEN_WIDTH + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - rectangle.getSize().x / 2,
			SCREEN_HEIGHT - GROUND_HEIGHT - rectangle.getSize().y);
	}
	else if (upgradeType == Shield)
	{
		rectangle.setPosition(SCREEN_WIDTH + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - rectangle.getSize().x / 2,
			SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f - rectangle.getSize().y);
	}
}
Upgrade::Upgrade(UpgradeType upType, sf::Vector2f size)
	:rectangle(size)
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, velocity(0.0f, 0.0f), floatSpeed(25.0f)
	, floatHeight(1.25f)
	, active(true)
	, upgradeType(upType)
{
	if (upgradeType == Health)
	{
		rectangle.setPosition(SCREEN_WIDTH + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - rectangle.getSize().x / 2,
			SCREEN_HEIGHT - GROUND_HEIGHT - rectangle.getSize().y);
	}
	else if (upgradeType == Shield)
	{
		rectangle.setPosition(SCREEN_WIDTH + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - rectangle.getSize().x / 2,
			SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f - rectangle.getSize().y);
	}
	else if (upgradeType == Speed)
	{
		rectangle.setPosition(rectangle.getSize().x * 2, 
			SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f - rectangle.getSize().y);
	}
	else if (upgradeType == RifleUp)
	{
		rectangle.setPosition(SCREEN_WIDTH * 2.5 - (rectangle.getSize().x * 2),
			SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f - rectangle.getSize().y);
	}
}

/* FUNCTIONS */
void Upgrade::update(sf::Time deltaTime)
{
	//Upgrade's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//update Upgrade's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;

	if (upgradeType == Health)
	{
		if (rectangle.getPosition().y == SCREEN_HEIGHT - GROUND_HEIGHT - rectangle.getSize().y)
			velocity.y = -1.0f;
		else if (rectangle.getPosition().y <= SCREEN_HEIGHT - GROUND_HEIGHT - rectangle.getSize().y * floatHeight)
			velocity.y = 1.0f;
	}

	else if (upgradeType == Shield || upgradeType == Speed || upgradeType == RifleUp)
	{
		if (rectangle.getPosition().y == SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f - rectangle.getSize().y)
			velocity.y = -1.0f;
		else if (rectangle.getPosition().y <= SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f - rectangle.getSize().y * floatHeight)
			velocity.y = 1.0f;
	}

	rectangle.move(velocity * floatSpeed * deltaTime.asSeconds());
}

void Upgrade::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

/* DECONSTRUCTORS */
Upgrade::~Upgrade()
{
}
