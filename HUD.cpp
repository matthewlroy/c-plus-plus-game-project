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
HUD::HUD()
	:rectangle(sf::Vector2f(320.0f, 100.0f))
	, hud_tex()
	, health(), shield(false), speed(false), hudWeapon(Gun), rifleBullets(0)
	, shieldDurability()
	, healthbar_tex(), healthbar()
	, shieldbar_tex(), shieldbar()
	, speedbar_tex(), speedbar()
	, riflebar_tex(), riflebar()
	, healthbarBG(sf::Vector2f(80.0f, 16.0f)), shieldbarBG(sf::Vector2f(48.0f, 16.0f)), speedbarBG(sf::Vector2f(64.0f, 16.0f)), riflebarBG(sf::Vector2f(128.0f, 16.0f))
	, _speedDuration(0.0f), speedDuration(0)
	, gun_tex(), rifle_tex()
	, weapon()
	, kills(0) , ARDARLING(), kills_text()

{
	if (!healthbar_tex.loadFromFile("Data/Textures/healthbar.png")) std::cout << "ERROR: HUD::HUD could not load 'healthbar_tex'...\n";
	healthbar.setTexture(healthbar_tex);
	healthbar.setTextureRect(sf::IntRect(0, 0, 80, 16));
	healthbarBG.setFillColor(gray);

	if (!shieldbar_tex.loadFromFile("Data/Textures/shieldbar.png")) std::cout << "ERROR: HUD::HUD could not load 'shieldbar_tex'...\n";
	shieldbar.setTexture(shieldbar_tex);
	shieldbar.setTextureRect(sf::IntRect(0, 0, 48, 16));
	shieldbarBG.setFillColor(gray);

	if (!speedbar_tex.loadFromFile("Data/Textures/speedbar.png")) std::cout << "ERROR: HUD::HUD could not load 'speedbar_tex'...\n";
	speedbar.setTexture(speedbar_tex);
	speedbar.setTextureRect(sf::IntRect(0, 0, 64, 16));
	speedbarBG.setFillColor(gray);

	if (!riflebar_tex.loadFromFile("Data/Textures/riflebar.png")) std::cout << "ERROR: HUD::HUD could not load 'riflebar_tex'...\n";
	riflebar.setTexture(riflebar_tex);
	riflebar.setTextureRect(sf::IntRect(0, 0, 128, 16));
	riflebarBG.setFillColor(gray);

	rectangle.setPosition(0.0f, SCREEN_HEIGHT - rectangle.getSize().y);
	healthbar.setPosition(rectangle.getPosition().x + 94.0f, rectangle.getPosition().y + 14.0f);
	shieldbar.setPosition(rectangle.getPosition().x + 94.0f + 80.0f + 6.0f, rectangle.getPosition().y + 14.0f);
	speedbar.setPosition(rectangle.getPosition().x + 94.0f + 80.0f + 48.0f + 12.0f, rectangle.getPosition().y + 14.0f);
	riflebar.setPosition(rectangle.getPosition().x + riflebarBG.getSize().x + 46.0f, rectangle.getPosition().y + 40.0f);

	//weapons
	if (!gun_tex.loadFromFile("Data/Textures/gun.png")) std::cout << "ERROR: HUD::HUD could not load 'gun_tex'...\n";
	if (!rifle_tex.loadFromFile("Data/Textures/rifle.png")) std::cout << "ERROR: HUD::HUD could not load 'rifle_tex'...\n";

	//text
	if (!ARDARLING.loadFromFile("Data/Fonts/ARDARLING.ttf")) std::cout << "ERROR: HUD::HUD could not load 'ARDARLING'...\n";
	kills_text.setFont(ARDARLING);
	kills_text.setCharacterSize(22);
	kills_text.setColor(lime_green);
	//kills_text.setString("0");
	kills_text.setPosition(239.0f, SCREEN_HEIGHT - rectangle.getSize().y + 56.0f);
}

/* FUNCTIONS */
void HUD::create(const std::string& path)
{
	if (!hud_tex.loadFromFile(path)) std::cout << "ERROR: HUD::create could not load 'hud_tex'...\n";
	rectangle.setTexture(&hud_tex);
}

void HUD::update(sf::Time deltaTime)
{
	//std::cout << health << std::endl;

	healthbarBG.setPosition(healthbar.getPosition().x, healthbar.getPosition().y);
	shieldbarBG.setPosition(shieldbar.getPosition().x, shieldbar.getPosition().y);
	speedbarBG.setPosition(speedbar.getPosition().x, speedbar.getPosition().y);
	riflebarBG.setPosition(riflebar.getPosition().x, riflebar.getPosition().y);

	speedDuration = 4 - (int)_speedDuration;
	if (speedDuration <= 0) speedDuration = 0;
	//std::cout << speedDuration << std::endl;

	if (hudWeapon == Gun)
	{
		weapon.setTextureRect(sf::IntRect(0, 0, 18, 13));
		weapon.setPosition(130.0f, SCREEN_HEIGHT - rectangle.getSize().y + 42.0f);
		weapon.setTexture(gun_tex);
	}
	else if (hudWeapon == Rifle)
	{
		weapon.setTextureRect(sf::IntRect(0, 0, 26, 16));
		weapon.setPosition(125.0f, SCREEN_HEIGHT - rectangle.getSize().y + 40.0f);
		weapon.setTexture(rifle_tex);
	}

	//std::cout << hudWeapon << std::endl;
}

void HUD::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);

	window.draw(healthbarBG);
	healthbar.setTextureRect(sf::IntRect(0, 0, 16*health, 16));
	window.draw(healthbar);

	window.draw(shieldbarBG);
	shieldbar.setTextureRect(sf::IntRect(0, 0, 16 * shieldDurability, 16));
	if (shield) window.draw(shieldbar);

	window.draw(speedbarBG);
	speedbar.setTextureRect(sf::IntRect(0, 0, 16 * speedDuration, 16));
	if (speed) window.draw(speedbar);

	window.draw(weapon);

	window.draw(riflebarBG);
	riflebar.setTextureRect(sf::IntRect(0, 0, 16 * rifleBullets, 16));
	if (hudWeapon == Rifle) window.draw(riflebar);

	//text
	std::stringstream kills_ss;
	kills_ss << kills;
	kills_text.setString(kills_ss.str());
	window.draw(kills_text);
}

/* DECONSTRUCTORS */
HUD::~HUD()
{
}
