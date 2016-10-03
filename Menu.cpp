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
Menu::Menu()
	:rectangle(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT))
	, menu_tex()
	, top(rectangle.getPosition().y), left(rectangle.getPosition().x), right(rectangle.getPosition().x + rectangle.getSize().x), bottom(rectangle.getPosition().y + rectangle.getSize().y)
	, width(rectangle.getSize().x), height(rectangle.getSize().y)
	, playButton_tex(), playButton(sf::Vector2f(180.0f, 56.0f))
	, quitButton_tex(), quitButton(sf::Vector2f(172.0f, 56.0f))
{
	if (!playButton_tex.loadFromFile("Data/Textures/playbutton.png")) std::cout << "ERROR: Menu::Menu could not load 'playButton_tex'...\n";
	if (!quitButton_tex.loadFromFile("Data/Textures/quitbutton.png")) std::cout << "ERROR: Menu::Menu could not load 'quitButton_tex'...\n";
	playButton.setTexture(&playButton_tex);
	quitButton.setTexture(&quitButton_tex);
}

/* FUNCTIONS */
void Menu::create(const std::string& path)
{
	if (!menu_tex.loadFromFile(path)) std::cout << "ERROR: Menu::create could not load 'menu_tex'...\n";
	rectangle.setTexture(&menu_tex);
}

void Menu::update(sf::Time deltaTime)
{
	//Menu's properties
	width = rectangle.getSize().x;
	height = rectangle.getSize().y;

	//update Menu's collisions
	top = rectangle.getPosition().y;
	left = rectangle.getPosition().x;
	right = rectangle.getPosition().x + width;
	bottom = rectangle.getPosition().y + height;

	//button positions
	playButton.setPosition(sf::Vector2f(551.0f, 334.0f));
	quitButton.setPosition(sf::Vector2f(551.0f, 433.0f));
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
	window.draw(playButton);
	window.draw(quitButton);
}

/* DECONSTRUCTORS */
Menu::~Menu()
{
}
