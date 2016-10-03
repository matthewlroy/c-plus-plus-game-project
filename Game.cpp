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

/* CLASSES */
std::vector<Terrain> terrain_vec;
Player player;
Weapon gun;
std::vector<Bullet> bullet_vec;
std::vector<Enemy> enemy_vec;
HUD hud;
std::vector<EnemyBullet> enemyBullet_vec;
std::vector<Upgrade> healthUpgrade_vec;
std::vector<Upgrade> shieldUpgrade_vec;
std::vector<Upgrade> speedUpgrade_vec;
std::vector<Upgrade> rifleUpgrade_vec;
Menu menu;

/* NOTES!!!
/////////////////////////////////////////////////////////////// FOR THE NEXT VIDEO
{ }{ } {} {} {} { }{ }{ } {} {} {} {} { }{ }{ }{ }{ } {} {
TBD;
{ }{ } {} {} {} { }{ }{ } {} {} {} {} { }{ }{ }{ }{ } {} {
/////////////////////////////////////////////////////////////// FOR THE NEXT VIDEO

////////////////////
// 	  URGENT      //
////////////////////
-NEED TO START ENEMY TIMERS ONLY WHEN PLAYER APPEARS;
-ADD IN PROPERTY OF RIFLE BULLETS;
-ADD IN KILLS FONT TO BE MATCHING HUD;
-NEED TO FIX 'CLANKY' ROTATION OF GUN;
-NEED TO CAP ROTATION ANGLE OF BULLET SHOT;
-DON'T WANT BULLET TO BE SHOT DIRECTLY DOWN OR UP;
-NEED TO FIX UP THE PLAYER CHANGING DIRECTION;
	-PLAYER FACES LEFT AND RIGHT TOO LATE;
	-NEED TO CHANGE DIRECTION WHEN MOUSE IS CLOSER TO PLAYER;
-NEED TO FIX BULLET VELOCITY AND PLAYER'S FOWARD VELOCITY;	**************URGENT*************
-CHANGE UPGRADE TIMERS BACK;
-IF GAME IS PAUSED, DON'T RESTART THE CLOCKS;
-ADD IN LIGHTNING FAST UPGRADE; (SECOND ONE);

////////////////////
// 	  FIXES       //
////////////////////
-NEED TO FIX THE CAMERA VIEW FOLLOWING PLAYER;
	-CHANGE THE CAMERA BASED ON PLAYER FACING;
		-RIGHT OR LEFT;
-NEED TO FIX UP TERRAIN AND PLAYER COLLISION CODE;
-ENEMY GRAVITY FALLS TOO FAST-NEEDS TO BE FIXED;
-NEED TO FIX PLAYER FALLING THROUGH PLATFORM;
	-HAPPENS ON BOTTOM AND LEFT COLLISION;
		-ON SECOND LEVEL;
-NEED TO FIX WHERE BULLET SHOOTS OUT FROM;
	-ADD IN ROTATION TO THE SHOOTING ANGLE;
-WHITE BOX WHEN BULLETS ARE FIRED;
-MAKE NEW SOUND FOR PLAYER FALLING OFF WORLD; ( SCREAMING );
-FIX THE PLAYER HURT SOUND; ( SOUNDS WEIRD ) ;
-WHITE BOX WHEN ENEMY BULLETS ARE FIRED;
-FIX THE ENEMY FACING CODE!!! (DOES NOT WORK WHEN SPAWN TOO CLOSE);
-CHANGE THE SOUND WHEN SHOT BY A LASERBEAM (PLAYER);
-FIX WHERE THE ENEMY SHOOTS ( ANGLES );
-MAKE HEALTH UPGRADE BOUNCE UP AND DOWN ( FLOATING ANIM THROUGH CODE );
-FIX MENU TEXT AND SHTUFF;

////////////////////
// 	  TO-DO       //
////////////////////
-NEED TO FINISH THE MAP;
	-ADD IN ALL PLATFORMS;
-ENEMY AI;
	-ENEMY JUMPING, PLATFORM DETECTION, BULLET DODGING;
-ENEMY PHYSICS (COLLISION DETECTION AND HANDLING)
-ENEMY JUMPING PHYSICS ON RED PLATFORM;
-ENEMY HEALTH;
-ANIMATIONS;
-WEAPON UPGRADES;
-MINIMAP;
-RESPAWN AFTER DEAD ( HEALTH == 0);
-MENUS!!!!!;

NOTES!!! */

/* CONSTRUCTORS */
Game::Game()
	:window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game", sf::Style::Titlebar | sf::Style::Close)
	, TIME_PER_FRAME(sf::seconds(1.0f / 60.0f))
	, gameState(PlayMode), currentWeapon(Gun)
	, aKey(false), dKey(false), wKey(false), sKey(false), escKey(false)
	, mouse_pixelPos(), mouse_worldPos()
	, mouse_leftClick(false), mouse_rightClick(false)
	, gravity(60.0f), jumpPlatform_degree(3.5f)
	, healthUpgrade_clock(), healthUpgrade_timer(), HEALTH_UPGRADE_SPAWN_DELAY(2.0f)
	, shieldUpgrade_clock(), shieldUpgrade_timer(), SHIELD_UPGRADE_SPAWN_DELAY(2.0f)
	, speedUpgrade_clock(), speedUpgrade_timer(), SPEED_UPGRADE_SPAWN_DELAY(2.0f)
	, rifleUpgrade_clock(), rifleUpgrade_timer(), RIFLE_UPGRADE_SPAWN_DELAY(2.0f)
	, jump_buff(), jump_sound()
	, jumpPlatform_buff(), jumpPlatform_sound()
	, shoot_buff(), shoot_sound()
	, playerHurt_buff(), playerHurt_sound()
	, enemyHurt_buff(), enemyHurt_sound()
	, enemyShoot_buff(), enemyShoot_sound()
	, healthUpgrade_buff(), healthUpgrade_sound()
	, shieldUpgrade_buff(), shieldUpgrade_sound()
	, speedUpgrade_buff(), speedUpgrade_sound()
	, rifleUpgrade_buff(), rifleUpgrade_sound()
	, bullet_tex(), enemy_tex(), enemyBullet_tex()
	, healthUpgrade_tex(), shieldUpgrade_tex(), speedUpgrade_tex(), rifleUpgrade_tex(), rifleBullet_tex()
	, jumpPlatform_tex(), ground_tex(), bridge_tex(), platform_tex(), agPlatform_tex()
{
	//window properties
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	
	//environmental
	addterrain_vec();
	spawnEnemies();
	loadData();

	//creation functions
	player.create("Data/Textures/player.png");
	gun.create("Data/Textures/gun.png");
	hud.create("Data/Textures/hud.png");
	healthUpgrade_vec.push_back(Upgrade(UpgradeType::Health, sf::Vector2f(46.0f, 46.0f)));
	shieldUpgrade_vec.push_back(Upgrade(UpgradeType::Shield, sf::Vector2f(44.0f, 43.0f)));
	speedUpgrade_vec.push_back(Upgrade(UpgradeType::Speed, sf::Vector2f(37.0f, 33.0f)));
	rifleUpgrade_vec.push_back(Upgrade(UpgradeType::RifleUp, sf::Vector2f(30.0f, 20.0f)));
	menu.create("Data/Textures/menu.png");
}

/* FUNCTIONS */
void Game::run()
{
	sf::Clock clock;
	sf::Time TIME_SINCE_LAST_UPDATE = sf::Time::Zero;
	while (window.isOpen())
	{
		TIME_SINCE_LAST_UPDATE += clock.restart();
		while (TIME_SINCE_LAST_UPDATE > TIME_PER_FRAME)
		{
			TIME_SINCE_LAST_UPDATE -= TIME_PER_FRAME;
			events();
			update(TIME_PER_FRAME);
		}
		render();
	}
}
void Game::events()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			handleKeyboardInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleKeyboardInput(event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			handleMouseInput(event.mouseButton.button, true);
			break;
		case sf::Event::MouseButtonReleased:
			handleMouseInput(event.mouseButton.button, false);
			break;
		}
	}
}

//handle inputs from computer
void Game::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Escape) escKey = isPressed;
	if (key == sf::Keyboard::A) aKey = isPressed;
	else if (key == sf::Keyboard::D) dKey = isPressed;
	else if (key == sf::Keyboard::W) wKey = isPressed;
	else if (key == sf::Keyboard::S) sKey = isPressed;
}
void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed)
{
	if (button == sf::Mouse::Left) mouse_leftClick = isPressed;
	else if (button == sf::Mouse::Right) mouse_rightClick = isPressed;
}

/* GAME UPDATES */
void Game::update(sf::Time deltaTime)
{
	//mouse update
	mouse_pixelPos = sf::Mouse::getPosition(window);
	mouse_worldPos = window.mapPixelToCoords(mouse_pixelPos);

	changeGameState();

	if (gameState == MenuMode)
	{
		menu.update(deltaTime);

		MENU_HANDLING_button_properties();
	}
	else if (gameState == PlayMode)
	{
		//updates
		player.update(deltaTime);

		for (int i = 0; i < terrain_vec.size(); i++)
		{
			if (terrain_vec[i].terrainType == JumpPlatform) terrain_vec[i].rectangle.setTexture(&jumpPlatform_tex);
			if (terrain_vec[i].terrainType == Ground) terrain_vec[i].rectangle.setTexture(&ground_tex);
			if (terrain_vec[i].terrainType == Bridge) terrain_vec[i].rectangle.setTexture(&bridge_tex);
			if (terrain_vec[i].terrainType == Platform) terrain_vec[i].rectangle.setTexture(&platform_tex);
			if (terrain_vec[i].terrainType == AGPlatform) terrain_vec[i].rectangle.setTexture(&agPlatform_tex);
			terrain_vec[i].update(deltaTime);
		}

		gun.update(deltaTime);

		for (int i = 0; i < bullet_vec.size(); i++)
		{
			if (currentWeapon == Gun) bullet_vec[i].rectangle.setTexture(&bullet_tex);
			else if (currentWeapon == Rifle) bullet_vec[i].rectangle.setTexture(&rifleBullet_tex);
			bullet_vec[i].update(deltaTime);
		}

		for (int i = 0; i < enemy_vec.size(); i++)
		{
			enemy_vec[i].rectangle.setTexture(&enemy_tex);
			enemy_vec[i].update(deltaTime);
		}
		hud.update(deltaTime);

		for (int i = 0; i < enemyBullet_vec.size(); i++)
		{
			enemyBullet_vec[i].rectangle.setTexture(&enemyBullet_tex);
			enemyBullet_vec[i].update(deltaTime);
		}

		for (int i = 0; i < healthUpgrade_vec.size(); i++)
		{
			healthUpgrade_vec[i].rectangle.setTexture(&healthUpgrade_tex);
			healthUpgrade_vec[i].update(deltaTime);
		}

		for (int i = 0; i < shieldUpgrade_vec.size(); i++)
		{
			shieldUpgrade_vec[i].rectangle.setTexture(&shieldUpgrade_tex);
			shieldUpgrade_vec[i].update(deltaTime);
		}

		for (int i = 0; i < speedUpgrade_vec.size(); i++)
		{
			speedUpgrade_vec[i].rectangle.setTexture(&speedUpgrade_tex);
			speedUpgrade_vec[i].update(deltaTime);
		}

		for (int i = 0; i < rifleUpgrade_vec.size(); i++)
		{
			rifleUpgrade_vec[i].rectangle.setTexture(&rifleUpgrade_tex);
			rifleUpgrade_vec[i].update(deltaTime);
		}

		//player
		GAME_HANDLING_player_movement(deltaTime);
		COLLISION_DETECTION_player_terrain();
		COLLISION_HANDLING_player_terrain();

		//weapon
		GAME_HANDLING_player_facing();
		GAME_HANDLING_weapon_rotation();
		GAME_HANDLING_player_shoot();

		//bullets
		COLLISION_DETECTION_bullet_terrain();
		GAME_HANDLING_inactive_bullet();

		//enemies
		GAME_HANDLING_enemy_add();
		GAME_HANDLING_enemy_physics();
		GAME_HANDLING_enemy_AI();
		COLLISION_DETECTION_bullet_enemy();
		COLLISION_DETECTION_player_enemy();
		GAME_HANDLING_inactive_enemy();

		//enemyBullets
		GAME_HANDLING_enemyBullet_shoot();
		GAME_HANDLING_inactive_enemyBullet();
		COLLISION_DETECTION_player_enemyBullet();

		//upgrades
		GAME_HANDLING_spawn_upgrade();
		COLLISION_DETECTION_player_upgrade();
		GAME_HANDLING_inactive_upgrade();

		GAME_HANDLING_shield_active();
		GAME_HANDLING_shield_inactive();

		GAME_HANDLING_speed_active();

		GAME_HANDLING_rifle_inactive();

		//HUD
		hud.health = player.health;
		hud.shield = player.shield;
		hud.shieldDurability = player.shieldDurability;
		hud.speed = player.speed;
		hud._speedDuration = player.speedDuration_timer.asSeconds();
		hud.rifleBullets = player.rifleBullets;

		//weapon properties
		if (player.rifleBullets <= 0)
		{
			hud.hudWeapon = Gun;
			gun.weaponCurrentWeapon = Gun;
		}
		else
		{
			hud.hudWeapon = Rifle;
			gun.weaponCurrentWeapon = Rifle;
		}
	}
}
void Game::changeGameState()
{
	if (escKey)
	{
		if (gameState == MenuMode)
			gameState = PlayMode;
		else if (gameState == PlayMode)
			gameState = MenuMode;
		escKey = false;
	}
}
void Game::MENU_HANDLING_button_properties()
{
	//playbutton
	if (menu.playButton.getGlobalBounds().contains(mouse_pixelPos.x, mouse_pixelPos.y))
	{
		menu.playButton.setFillColor(sf::Color(255, 255, 255, 144));

		if (mouse_leftClick)
		{
			gameState = PlayMode;
			mouse_leftClick = false;
		}
	}
	else menu.playButton.setFillColor(sf::Color(255, 255, 255, 255));

	//quitbutton
	if (menu.quitButton.getGlobalBounds().contains(mouse_pixelPos.x, mouse_pixelPos.y))
	{
		menu.quitButton.setFillColor(sf::Color(255, 255, 255, 144));

		if (mouse_leftClick)
		{
			window.close();
			mouse_leftClick = false;
		}
	}
	else menu.quitButton.setFillColor(sf::Color(255, 255, 255, 255));
}

//player
void Game::GAME_HANDLING_player_movement(sf::Time deltaTime)
{
	//player movement
	if (aKey && !player.leftCollision) player.velocity.x = -player.moveSpeed;
	else if (dKey && !player.rightCollision) player.velocity.x = player.moveSpeed;
	else player.velocity.x = 0;

	//player jumping
	if (wKey && !player.isJumping && !player.agCollision)
	{
		player.velocity.y = -player.jumpSpeed;
		jump_sound.play();
	}
	player.rectangle.move(player.velocity * deltaTime.asSeconds());

	//reset player position
	if (player.rectangle.getPosition().y > 3000.0f)
	{
		if (!player.shield)
			player.health--;
		else if (player.shield)
			player.shieldDurability--;
		playerHurt_sound.play();
		player.rectangle.setPosition(100.0f, 100.0f);
	}
}
void Game::COLLISION_DETECTION_player_terrain()
{
	for (int i = 0; i < terrain_vec.size(); i++)
	{
		if (player.rectangle.getGlobalBounds().intersects(terrain_vec[i].rectangle.getGlobalBounds()))
		{
			if (player.right >= terrain_vec[i].left && player.left < terrain_vec[i].left)
			{
				player.rightCollision = true;
				player.rightCollisionLocation = terrain_vec[i].left;
			}
			if (player.left <= terrain_vec[i].right && player.right > terrain_vec[i].right)
			{
				player.leftCollision = true;
				player.leftCollisionLocation = terrain_vec[i].right;
			}
			if (player.bottom <= terrain_vec[i].top && player.top < terrain_vec[i].top)
			{
				player.rightCollision = false;
				player.leftCollision = false;
				player.bottomCollision = true;
				player.bottomCollisionLocation = terrain_vec[i].top;

				if (terrain_vec[i].terrainType == JumpPlatform)
				{
					player.bottomCollision = false;
					player.velocity.y = -player.jumpSpeed * jumpPlatform_degree;
					player.isJumping = true;

					jumpPlatform_sound.play();
				}

				if (terrain_vec[i].terrainType == AGPlatform)
				{
					player.bottomCollision = true;
					player.agCollision = true;
				}
				else player.agCollision = false;

				if (terrain_vec[i].terrainType == Platform && sKey)
				{
					sKey = false;
					player.bottomCollision = false;
				}
			}
			break;
		}
		else
		{
			player.bottomCollision = false;
			player.rightCollision = false;
			player.leftCollision = false;
		}
	}
}
void Game::COLLISION_HANDLING_player_terrain()
{
	if (!player.rightCollision)
	{
	}
	else
	{
		player.rectangle.setPosition(player.rightCollisionLocation - player.width, player.rectangle.getPosition().y);
		player.velocity.x = 0;
	}

	if (!player.leftCollision)
	{
	}
	else
	{
		player.rectangle.setPosition(player.leftCollisionLocation, player.rectangle.getPosition().y);
		player.velocity.x = 0;
	}

	if (!player.bottomCollision)
	{
		player.velocity.y += gravity;
		player.isJumping = true;
	}
	else
	{
		player.rectangle.setPosition(player.rectangle.getPosition().x, player.bottomCollisionLocation - player.height);
		player.velocity.y = 0;
		player.isJumping = false;
	}
}

//weapon
void Game::GAME_HANDLING_player_facing()
{
	//std::cout << "MOUSE POS: (" << mouse_worldPos.x << "," << mouse_worldPos.y << ")...\n";
	//std::cout << "PLAYER POS: (" << player.rectangle.getPosition().x << "," << player.rectangle.getPosition().y << ")...\n";

	if (mouse_worldPos.x > player.rectangle.getPosition().x + player.width / 2) player.playerFacing = Right;
	else if (mouse_worldPos.x < player.rectangle.getPosition().x + player.width / 2) player.playerFacing = Left;

	if (player.playerFacing == Right)
	{
		gun.rectangle.setPosition(player.rectangle.getPosition().x + player.width,
			player.rectangle.getPosition().y + player.height / 2);

		if (gun.rectangle.getScale().x != 1) gun.rectangle.scale(-1.0f, 1.0f);
	}
	else if (player.playerFacing == Left)
	{
		gun.rectangle.setPosition(player.rectangle.getPosition().x,
			player.rectangle.getPosition().y + player.height / 2);

		if (gun.rectangle.getScale().x != -1) gun.rectangle.scale(-1.0f, 1.0f);
	}
}
void Game::GAME_HANDLING_weapon_rotation()
{
	float rotAngle;

	//std::cout << gun.rectangle.getRotation() << std::endl;

	if (player.playerFacing == Right)
	{
		rotAngle = atan2((mouse_worldPos.x - gun.rectangle.getPosition().x), (mouse_worldPos.y - gun.rectangle.getPosition().y)) * (180 / PI);
		gun.rectangle.setRotation(90.0f - rotAngle);
	}
	else if (player.playerFacing == Left)
	{
		rotAngle = atan2((mouse_worldPos.y - gun.rectangle.getPosition().y), (gun.rectangle.getPosition().x - mouse_worldPos.x)) * (180 / PI);
		gun.rectangle.setRotation(0.0f - rotAngle);
	}
}
void Game::GAME_HANDLING_player_shoot()
{
	if (mouse_leftClick)
	{
		//set bullet velocity
		float gunX = gun.rectangle.getPosition().x;
		float gunY = gun.rectangle.getPosition().y;

		float angleX = mouse_worldPos.x - gunX;
		float angleY = mouse_worldPos.y - gunY;

		//if (player.playerFacing == Right)
		//{
		//	if (player.velocity.x > 0) angleX = angleX + player.velocity.x;
		//	else if (player.velocity.x < 0) angleX = angleX - player.velocity.x;
		//}
		//else if (player.playerFacing == Left)
		//{
		//	if (player.velocity.x < 0) angleX = angleX + player.velocity.x;
		//	else if (player.velocity.x > 0) angleX = angleX - player.velocity.x;
		//}

		float vectorLength = sqrt(angleX*angleX + angleY*angleY);

		float directionX = angleX / vectorLength;
		float directionY = angleY / vectorLength;

		float velocityX = directionX;
		float velocityY = directionY;

		//std::cout << velocityX << std::endl;

		//fire bullet
		shoot_sound.play();
		if (player.playerFacing == Right)
		{
			Bullet newBullet(sf::Vector2f(gunX, gunY), sf::Vector2f(velocityX, velocityY));
			bullet_vec.push_back(newBullet);
		}
		else if (player.playerFacing == Left)
		{
			Bullet newBullet(sf::Vector2f(gunX - 10.0f, gunY), sf::Vector2f(velocityX, velocityY));
			bullet_vec.push_back(newBullet);
		}

		//rifle upgrade active
		if (currentWeapon == Rifle)
		{
			player.rifleBullets--;
			mouse_leftClick = false;
		}

		mouse_leftClick = false;
	}
}

//bullets
void Game::COLLISION_DETECTION_bullet_terrain()
{
	for (int i = 0; i < terrain_vec.size(); i++)
	{
		for (int j = 0; j < bullet_vec.size(); j++)
		{
			if (terrain_vec[i].terrainType != JumpPlatform)
			{
				if (terrain_vec[i].rectangle.getGlobalBounds().intersects(bullet_vec[j].rectangle.getGlobalBounds()))
					bullet_vec[j].active = false;
			}
		}
	}
}
void Game::GAME_HANDLING_inactive_bullet()
{
	for (int i = 0; i < bullet_vec.size(); i++)
	{
		if (bullet_vec[i].active == false)
			bullet_vec.erase(bullet_vec.begin() + i);
	}
}

//enemies
void Game::GAME_HANDLING_enemy_add()
{
	if (mouse_rightClick)
	{
		enemy_vec.push_back(Enemy(sf::Vector2f(mouse_worldPos.x, mouse_worldPos.y)));
		mouse_rightClick = false;
	}
}
void Game::GAME_HANDLING_enemy_physics()
{
	for (int i = 0; i < enemy_vec.size(); i++)	/* TEMPORARY */
	{
		for (int j = 0; j < terrain_vec.size(); j++)
		{
			if (enemy_vec[i].rectangle.getGlobalBounds().intersects(terrain_vec[j].rectangle.getGlobalBounds()))
			{
				enemy_vec[i].rectangle.setPosition(enemy_vec[i].rectangle.getPosition().x, terrain_vec[j].top - enemy_vec[i].height);
				enemy_vec[i].velocity.y = 0;
			}
			else
			{
				enemy_vec[i].velocity.y += gravity;
				if (enemy_vec[i].rectangle.getPosition().y > 3000.0f) enemy_vec[i].active = false;
			}
		}
	}
}
void Game::GAME_HANDLING_enemy_AI()
{
	//enemy movement
	float posRight = player.right + player.width * 2;
	float posLeft = player.left - player.width * 2;

	for (int i = 0; i < enemy_vec.size(); i++)
	{
		//std::cout << "DISTANCE: " << abs(posRight - enemy_vec[i].left) << std::endl;
		//std::cout << abs(player.rectangle.getPosition().x - enemy_vec[i].rectangle.getPosition().x) << std::endl;
		//std::cout << abs(player.rectangle.getPosition().y - enemy_vec[i].rectangle.getPosition().y) << std::endl;

		if (abs(player.rectangle.getPosition().x - enemy_vec[i].rectangle.getPosition().x) < 963.0f &&
			abs(player.rectangle.getPosition().y - enemy_vec[i].rectangle.getPosition().y) < 100.0f)
		{
			if (enemy_vec[i].left >= posRight)
			{
				enemy_vec[i].enemyFacing = eLeft;
				enemy_vec[i].velocity.x = -enemy_vec[i].moveSpeed;
			}
			else if (enemy_vec[i].right <= posLeft)
			{
				enemy_vec[i].enemyFacing = eRight;
				enemy_vec[i].velocity.x = enemy_vec[i].moveSpeed;
			}
			else enemy_vec[i].velocity.x = 0;
		}
		else enemy_vec[i].velocity.x = 0;
	}
}
void Game::COLLISION_DETECTION_bullet_enemy()
{
	for (int i = 0; i < enemy_vec.size(); i++)
	{
		for (int j = 0; j < bullet_vec.size(); j++)
		{
			if (enemy_vec[i].rectangle.getGlobalBounds().intersects(bullet_vec[j].rectangle.getGlobalBounds()))
			{
				hud.kills++;
				enemyHurt_sound.play();
				bullet_vec[j].active = false;
				enemy_vec[i].active = false;
			}
		}
	}
}
void Game::COLLISION_DETECTION_player_enemy()
{
	for (int i = 0; i < enemy_vec.size(); i++)
	{
		if (enemy_vec[i].rectangle.getGlobalBounds().intersects(player.rectangle.getGlobalBounds()))
		{
			if (!player.shield) player.health--;
			else if (player.shield) player.shieldDurability--;
			enemy_vec[i].active = false;
			playerHurt_sound.play();
		}
	}
}
void Game::GAME_HANDLING_inactive_enemy()
{
	for (int i = 0; i < enemy_vec.size(); i++)
	{
		if (!enemy_vec[i].active)
			enemy_vec.erase(enemy_vec.begin() + i);
	}
}

//enemyBullets
void Game::GAME_HANDLING_enemyBullet_shoot()
{
	for (int i = 0; i < enemy_vec.size(); i++)
	{
		if (enemy_vec[i].enemyBullet_timer.asSeconds() >= enemy_vec[i].ENEMY_BULLET_SHOOT_DELAY)
		{
			if (abs(player.rectangle.getPosition().x - enemy_vec[i].rectangle.getPosition().x) < 963.0f &&
				abs(player.rectangle.getPosition().y - enemy_vec[i].rectangle.getPosition().y) < 100.0f)
			{
				enemyShoot_sound.play();
				if (enemy_vec[i].enemyFacing == eLeft)
				{
					EnemyBullet newEnemyBullet(sf::Vector2f(enemy_vec[i].left - 19.0f, enemy_vec[i].rectangle.getPosition().y + 4.0f));
					newEnemyBullet.velocity.x = -newEnemyBullet.moveSpeed + enemy_vec[i].velocity.x;
					enemyBullet_vec.push_back(newEnemyBullet);
				}
				if (enemy_vec[i].enemyFacing == eRight)
				{
					EnemyBullet newEnemyBullet(sf::Vector2f(enemy_vec[i].right, enemy_vec[i].rectangle.getPosition().y + 4.0f));
					newEnemyBullet.velocity.x = newEnemyBullet.moveSpeed + enemy_vec[i].velocity.x;
					enemyBullet_vec.push_back(newEnemyBullet);
				}
				enemy_vec[i].enemyBullet_clock.restart();
			}
		}
	}
}
void Game::GAME_HANDLING_inactive_enemyBullet()
{
	for (int i = 0; i < enemyBullet_vec.size(); i++)
	{
		if (!enemyBullet_vec[i].active)
		{
			enemyBullet_vec.erase(enemyBullet_vec.begin() + i);
		}
	}
}
void Game::COLLISION_DETECTION_player_enemyBullet()
{
	for (int i = 0; i < enemyBullet_vec.size(); i++)
	{
		if (enemyBullet_vec[i].rectangle.getGlobalBounds().intersects(player.rectangle.getGlobalBounds()))
		{
			if (!player.shield) player.health--;
			else if (player.shield) player.shieldDurability--;
			enemyBullet_vec[i].active = false;
			playerHurt_sound.play();
		}
	}
}

//upgrades
void Game::GAME_HANDLING_spawn_upgrade()
{
	//healths
	healthUpgrade_timer = healthUpgrade_clock.getElapsedTime();
	if (healthUpgrade_vec.size() == 0 && healthUpgrade_vec.size() < 2 && healthUpgrade_timer.asSeconds() >= HEALTH_UPGRADE_SPAWN_DELAY)
	{
		healthUpgrade_vec.push_back(Upgrade(UpgradeType::Health, sf::Vector2f(46.0f, 46.0f)));
		healthUpgrade_clock.restart();
	}

	//shields
	shieldUpgrade_timer = shieldUpgrade_clock.getElapsedTime();
	if (shieldUpgrade_vec.size() == 0 && shieldUpgrade_vec.size() < 2 && shieldUpgrade_timer.asSeconds() >= SHIELD_UPGRADE_SPAWN_DELAY)
	{
		shieldUpgrade_vec.push_back(Upgrade(UpgradeType::Shield, sf::Vector2f(44.0f, 43.0f)));
		shieldUpgrade_clock.restart();
	}

	//speeds
	speedUpgrade_timer = speedUpgrade_clock.getElapsedTime();
	if (speedUpgrade_vec.size() == 0 && speedUpgrade_vec.size() < 2 && speedUpgrade_timer.asSeconds() >= SPEED_UPGRADE_SPAWN_DELAY)
	{
		speedUpgrade_vec.push_back(Upgrade(UpgradeType::Speed, sf::Vector2f(37.0f, 33.0f)));
		speedUpgrade_clock.restart();
	}

	//rifle
	rifleUpgrade_timer = rifleUpgrade_clock.getElapsedTime();
	if (rifleUpgrade_vec.size() == 0 && rifleUpgrade_vec.size() < 2 && rifleUpgrade_timer.asSeconds() >= RIFLE_UPGRADE_SPAWN_DELAY)
	{
		rifleUpgrade_vec.push_back(Upgrade(UpgradeType::RifleUp, sf::Vector2f(30.0f, 20.0f)));
		rifleUpgrade_clock.restart();
	}
}
void Game::COLLISION_DETECTION_player_upgrade()
{
	//healths
	for (int i = 0; i < healthUpgrade_vec.size(); i++)
	{
		if (player.rectangle.getGlobalBounds().intersects(healthUpgrade_vec[i].rectangle.getGlobalBounds()) && player.health != 5)
		{
			healthUpgrade_sound.play();
			healthUpgrade_vec[i].active = false;
			player.health = 5;
			healthUpgrade_clock.restart();
		}
	}

	//shields
	for (int i = 0; i < shieldUpgrade_vec.size(); i++)
	{
		if (player.rectangle.getGlobalBounds().intersects(shieldUpgrade_vec[i].rectangle.getGlobalBounds()) && player.shieldDurability != 3)
		{
			shieldUpgrade_sound.play();
			shieldUpgrade_vec[i].active = false;
			player.shield = true;
			player.shieldDurability = 3;
			shieldUpgrade_clock.restart();
		}
	}

	//speeds
	for (int i = 0; i < speedUpgrade_vec.size(); i++)
	{
		if (player.rectangle.getGlobalBounds().intersects(speedUpgrade_vec[i].rectangle.getGlobalBounds()) && !player.speed)
		{
			speedUpgrade_sound.play();
			speedUpgrade_vec[i].active = false;
			player.speed = true;
			speedUpgrade_clock.restart();
			player.resetSpeedDuration();
		}
	}

	//rifles
	for (int i = 0; i < rifleUpgrade_vec.size(); i++)
	{
		if (player.rectangle.getGlobalBounds().intersects(rifleUpgrade_vec[i].rectangle.getGlobalBounds()) && player.rifleBullets < 8)
		{
			rifleUpgrade_sound.play();
			rifleUpgrade_vec[i].active = false;
			currentWeapon = Rifle;
			rifleUpgrade_clock.restart();
			player.rifleBullets = 8;
		}
	}
}
void Game::GAME_HANDLING_inactive_upgrade()
{
	//healths
	for (int i = 0; i < healthUpgrade_vec.size(); i++)
	{
		if (!healthUpgrade_vec[i].active)
			healthUpgrade_vec.erase(healthUpgrade_vec.begin() + i);
	}

	//shields
	for (int i = 0; i < shieldUpgrade_vec.size(); i++)
	{
		if (!shieldUpgrade_vec[i].active)
			shieldUpgrade_vec.erase(shieldUpgrade_vec.begin() + i);
	}

	//speeds
	for (int i = 0; i < speedUpgrade_vec.size(); i++)
	{
		if (!speedUpgrade_vec[i].active)
			speedUpgrade_vec.erase(speedUpgrade_vec.begin() + i);
	}

	//rifle
	for (int i = 0; i < rifleUpgrade_vec.size(); i++)
	{
		if (!rifleUpgrade_vec[i].active)
			rifleUpgrade_vec.erase(rifleUpgrade_vec.begin() + i);
	}
}

void Game::GAME_HANDLING_shield_active()
{
	//set shield position
	player.shield_rect.setPosition(player.rectangle.getPosition().x - (player.shield_rect.getSize().x - player.rectangle.getSize().x) / 2, 
		player.rectangle.getPosition().y - (player.shield_rect.getSize().y - player.rectangle.getSize().y) / 2);

	//std::cout << player.shieldDurability << std::endl;
}
void Game::GAME_HANDLING_shield_inactive()
{
	if (player.shieldDurability <= 0) player.shield = false;
}

void Game::GAME_HANDLING_speed_active()
{
	player.speed_rect.setPosition(player.rectangle.getPosition().x - (player.speed_rect.getSize().x - player.rectangle.getSize().x) / 2,
		player.rectangle.getPosition().y - (player.speed_rect.getSize().y - player.rectangle.getSize().y) / 2);
	if (player.speed)
	{
		player.moveSpeed = 1000.0f;
	}
	if (!player.speed)
	{
		player.moveSpeed = 400.0f;
	}
}

void Game::GAME_HANDLING_rifle_inactive()
{
	if (player.rifleBullets < 0)
	{
		currentWeapon = Gun;
	}
}

//environmental
void Game::addterrain_vec()
{
	//ground
	terrain_vec.push_back(Terrain(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT), sf::Vector2f(0.0f, SCREEN_HEIGHT - GROUND_HEIGHT), Ground)); //left
	terrain_vec.push_back(Terrain(sf::Vector2f(SCREEN_WIDTH / 2, 40.0f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_HEIGHT), Bridge)); //bridge
	terrain_vec.push_back(Terrain(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT), sf::Vector2f(SCREEN_WIDTH + SCREEN_WIDTH / 2, SCREEN_HEIGHT - GROUND_HEIGHT), Ground)); //right

	//jumpPlatforms
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT - GROUND_HEIGHT - 60.0f), JumpPlatform)); //left
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH * 2 - 100.0f, SCREEN_HEIGHT - GROUND_HEIGHT - 60.0f), JumpPlatform)); //right

	//platforms
	terrain_vec.push_back(Terrain(sf::Vector2f(SCREEN_WIDTH * 2.5, 40.0f), sf::Vector2f(0.0f, SCREEN_HEIGHT - GROUND_HEIGHT*3 - 675.0f), Platform)); //left

	/* TEMP */
	//////////////////////////////////
	//agPlatforms / etc
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH * 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - GROUND_HEIGHT), AGPlatform)); //right
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH * 2 + SCREEN_WIDTH / 2 + 201.0f, SCREEN_HEIGHT - GROUND_HEIGHT), AGPlatform)); //right
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH * 2 + SCREEN_WIDTH / 2 + 201.0f * 2, SCREEN_HEIGHT - GROUND_HEIGHT), AGPlatform)); //right
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH * 2 + SCREEN_WIDTH / 2 + 201.0f * 3, SCREEN_HEIGHT - GROUND_HEIGHT), AGPlatform)); //right
	terrain_vec.push_back(Terrain(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT), sf::Vector2f(SCREEN_WIDTH * 2 + SCREEN_WIDTH / 2 + 201.0f * 4 + 1.0f, SCREEN_HEIGHT - GROUND_HEIGHT), Ground)); //right
	terrain_vec.push_back(Terrain(sf::Vector2f(SCREEN_WIDTH * 2.5, 40.0f), sf::Vector2f(SCREEN_WIDTH * 2.5 - 1.0f, SCREEN_HEIGHT - GROUND_HEIGHT * 3 - 675.0f), Platform)); //left
	terrain_vec.push_back(Terrain(sf::Vector2f(202.0f, 32.0f), sf::Vector2f(SCREEN_WIDTH * 3.5 - 1.0f, SCREEN_HEIGHT - GROUND_HEIGHT - 60.0f), JumpPlatform)); //right
}
void Game::spawnEnemies()
{
	//std::cout << "spawning...\n";
	//bottom floor
	enemy_vec.push_back(Enemy(sf::Vector2f(1200.0f, 200.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(2200.0f, 200.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(3200.0f, 200.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(4200.0f, 200.0f)));

	//top floor
	enemy_vec.push_back(Enemy(sf::Vector2f(1200.0f, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(2200.0f, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(3200.0f, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(4200.0f, -800.0f)));

	//ending area
	enemy_vec.push_back(Enemy(sf::Vector2f(SCREEN_WIDTH * 3.5, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(SCREEN_WIDTH * 3.5 + 200.0f, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(SCREEN_WIDTH * 3.5 + 200.0f * 2, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(SCREEN_WIDTH * 3.5 + 200.0f * 3, -800.0f)));
	enemy_vec.push_back(Enemy(sf::Vector2f(SCREEN_WIDTH * 3.5 + 200.0f * 4, -800.0f)));
}
void Game::render()
{
	window.clear(gray);
	//views
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	//{
	//	sf::View miniMap(window.getDefaultView());
	//	miniMap.zoom(5.0f);
	//	window.setView(miniMap);
	//	player.draw(window);
	//	for (int i = 0; i < terrain_vec.size(); i++) terrain_vec[i].draw(window);
	//	for (int i = 0; i < bullet_vec.size(); i++)
	//	{
	//		if (!bullet_vec[i].rectangle.getGlobalBounds().intersects(gun.rectangle.getGlobalBounds()))
	//			bullet_vec[i].draw(window);
	//	}
	//	gun.draw(window);
	//	for (int i = 0; i < enemy_vec.size(); i++) enemy_vec[i].draw(window);
	//	for (int i = 0; i < enemyBullet_vec.size(); i++) enemyBullet_vec[i].draw(window);
	//}

	sf::View playerCamera(window.getDefaultView());
	playerCamera.setCenter(player.rectangle.getPosition().x + SCREEN_WIDTH / 4, player.rectangle.getPosition().y - GROUND_HEIGHT + player.height);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) playerCamera.zoom(2.6f);
	window.setView(playerCamera);

	player.draw(window);
	for (int i = 0; i < terrain_vec.size(); i++) terrain_vec[i].draw(window);
	for (int i = 0; i < bullet_vec.size(); i++)
	{
		if (!bullet_vec[i].rectangle.getGlobalBounds().intersects(gun.rectangle.getGlobalBounds()))
			bullet_vec[i].draw(window);
	}
	gun.draw(window);
	for (int i = 0; i < enemy_vec.size(); i++) enemy_vec[i].draw(window);
	for (int i = 0; i < enemyBullet_vec.size(); i++) enemyBullet_vec[i].draw(window);	
	for (int i = 0; i < healthUpgrade_vec.size(); i++) healthUpgrade_vec[i].draw(window);
	for (int i = 0; i < shieldUpgrade_vec.size(); i++) shieldUpgrade_vec[i].draw(window);
	for (int i = 0; i < speedUpgrade_vec.size(); i++) speedUpgrade_vec[i].draw(window);
	for (int i = 0; i < rifleUpgrade_vec.size(); i++) rifleUpgrade_vec[i].draw(window);

	window.setView(window.getDefaultView());
	hud.draw(window);
	if (gameState == MenuMode) menu.draw(window);
	window.setView(playerCamera);

	//sf::RectangleShape test(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	//test.setPosition(0.0f, 0.0f);
	//test.setFillColor(sf::Color(0, 0, 0, 0));
	//test.setOutlineColor(sf::Color::White);
	//test.setOutlineThickness(5.0f);
	//window.draw(test);
	window.display();
}
void Game::loadData()
{
	//sounds
	if (!jump_buff.loadFromFile("Data/Sounds/jump.wav")) std::cout << "ERROR: Game::loadData could not load 'jump_buff'...\n"; //player jumping
	jump_sound.setBuffer(jump_buff);

	if (!jumpPlatform_buff.loadFromFile("Data/Sounds/jumpplatform.wav")) std::cout << "ERROR: Game::loadData could not load 'jumpPlatform_buff'...\n"; //jumpPlatforms
	jumpPlatform_sound.setBuffer(jumpPlatform_buff);

	if (!shoot_buff.loadFromFile("Data/Sounds/shoot.wav")) std::cout << "ERROR: Game::loadData could not load 'shoot_buff'...\n"; //shoot
	shoot_sound.setBuffer(shoot_buff);
	if (!playerHurt_buff.loadFromFile("Data/Sounds/playerhurt.wav")) std::cout << "ERROR: Game::loadData could not load 'playerHurt_buff'...\n"; //player hurt
	playerHurt_sound.setBuffer(playerHurt_buff);

	if (!enemyHurt_buff.loadFromFile("Data/Sounds/enemyhurt.wav")) std::cout << "ERROR: Game::loadData could not load 'enemyHurt_buff'...\n"; //enemy hurt
	enemyHurt_sound.setBuffer(enemyHurt_buff);
	if (!enemyShoot_buff.loadFromFile("Data/Sounds/enemyshoot.wav")) std::cout << "ERROR: Game::loadData could not load 'enemyShoot_buff'...\n"; //enemy shoot
	enemyShoot_sound.setBuffer(enemyShoot_buff);

	if (!healthUpgrade_buff.loadFromFile("Data/Sounds/healthupgrade.wav")) std::cout << "ERROR: Game::loadData could not load 'healthUpgrade_buff'...\n"; //health upgrade
	healthUpgrade_sound.setBuffer(healthUpgrade_buff);
	if (!shieldUpgrade_buff.loadFromFile("Data/Sounds/shieldupgrade.wav")) std::cout << "ERROR: Game::loadData could not load 'shieldUpgrade_buff'...\n"; //shield upgrade
	shieldUpgrade_sound.setBuffer(shieldUpgrade_buff);
	if (!speedUpgrade_buff.loadFromFile("Data/Sounds/speedupgrade.wav")) std::cout << "ERROR: Game::loadData could not load 'speedUpgrade_buff'...\n"; //speed upgrade
	speedUpgrade_sound.setBuffer(speedUpgrade_buff);
	if (!rifleUpgrade_buff.loadFromFile("Data/Sounds/rifleupgrade.wav")) std::cout << "ERROR: Game::loadData could not load 'rifleUpgrade_buff'...\n"; //rifle upgrade
	rifleUpgrade_sound.setBuffer(rifleUpgrade_buff);

	//textures
	if (!bullet_tex.loadFromFile("Data/Textures/bullet.png")) std::cout << "ERROR: Game::loadData could not load 'bullet_tex'...\n"; //bullet
	if (!enemy_tex.loadFromFile("Data/Textures/enemy.png")) std::cout << "ERROR: Game::loadData could not load 'enemy_tex'...\n"; //enemy
	if (!enemyBullet_tex.loadFromFile("Data/Textures/enemybullet.png")) std::cout << "ERROR: Game::loadData could not load 'enemyBullet_tex'...\n"; //enemyBullet
	if (!healthUpgrade_tex.loadFromFile("Data/Textures/healthupgrade.png")) std::cout << "ERROR: Game::loadData could not load 'healthUpgrade_tex'...\n"; //healthUpgrade
	if (!shieldUpgrade_tex.loadFromFile("Data/Textures/shieldupgrade.png")) std::cout << "ERROR: Game::loadData could not load 'shieldUpgrade_tex'...\n"; //shieldUpgrade
	if (!speedUpgrade_tex.loadFromFile("Data/Textures/speedupgrade.png")) std::cout << "ERROR: Game::loadData could not load 'speedUpgrade_tex'...\n"; //speedUpgrade
	if (!rifleUpgrade_tex.loadFromFile("Data/Textures/rifleupgrade.png")) std::cout << "ERROR: Game::loadData could not load 'rifleUpgrade_tex'...\n"; //rifleUpgrade
	if (!rifleBullet_tex.loadFromFile("Data/Textures/riflebullet.png")) std::cout << "ERROR: Game::loadData could not load 'rifleBullet_tex'...\n"; //rifleBullet

	if (!jumpPlatform_tex.loadFromFile("Data/Textures/jumpplatform.png")) std::cout << "ERROR: Game::loadData could not load 'jumpPlatform_tex'...\n"; //jumpPlatform
	if (!ground_tex.loadFromFile("Data/Textures/ground.png")) std::cout << "ERROR: Game::loadData could not load 'ground_tex'...\n"; //ground
	if (!bridge_tex.loadFromFile("Data/Textures/bridge.png")) std::cout << "ERROR: Game::loadData could not load 'bridge_tex'...\n"; //bridge
	if (!platform_tex.loadFromFile("Data/Textures/platform.png")) std::cout << "ERROR: Game::loadData could not load 'platform_tex'...\n"; //platform
	if (!agPlatform_tex.loadFromFile("Data/Textures/agplatform.png")) std::cout << "ERROR: Game::loadData could not load 'agPlatform_tex'...\n"; //agPlatform
}

/* DECONSTRUCTORS */
Game::~Game()
{
}