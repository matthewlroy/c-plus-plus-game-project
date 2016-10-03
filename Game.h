#pragma once
//enumerations
enum GameState { MenuMode, PlayMode };
enum CurrentWeapon { Gun, Rifle };
class Game
{
public:
	Game();

	void run();

	~Game();

private:
	void events();
	void handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
	void handleMouseInput(sf::Mouse::Button button, bool isPressed);

	void changeGameState();
	void MENU_HANDLING_button_properties();

	void update(sf::Time deltaTime);

	//player
	void GAME_HANDLING_player_movement(sf::Time deltaTime);
	void COLLISION_DETECTION_player_terrain();
	void COLLISION_HANDLING_player_terrain();

	//weapon
	void GAME_HANDLING_player_facing();
	void GAME_HANDLING_weapon_rotation();
	void GAME_HANDLING_player_shoot();

	//bullets
	void COLLISION_DETECTION_bullet_terrain();
	void GAME_HANDLING_inactive_bullet();

	//enemies
	void GAME_HANDLING_enemy_add();
	void GAME_HANDLING_enemy_physics();
	void GAME_HANDLING_enemy_AI();
	void COLLISION_DETECTION_bullet_enemy();
	void COLLISION_DETECTION_player_enemy();
	void GAME_HANDLING_inactive_enemy();

	//enemyBullets
	void GAME_HANDLING_enemyBullet_shoot();
	void GAME_HANDLING_inactive_enemyBullet();
	void COLLISION_DETECTION_player_enemyBullet();

	//upgrades
	void GAME_HANDLING_spawn_upgrade();
	void COLLISION_DETECTION_player_upgrade();
	void GAME_HANDLING_inactive_upgrade();

	void GAME_HANDLING_shield_active();
	void GAME_HANDLING_shield_inactive();

	void GAME_HANDLING_speed_active();

	void GAME_HANDLING_rifle_inactive();

	//environmental
	void addterrain_vec();
	void spawnEnemies();
	void loadData();

	void render();
private:
	sf::RenderWindow window;
	const sf::Time TIME_PER_FRAME;

	GameState gameState;
	CurrentWeapon currentWeapon;

	//key variables
	bool aKey, dKey, wKey, sKey, escKey;

	//mouse variables
	sf::Vector2i mouse_pixelPos;
	sf::Vector2f mouse_worldPos;
	bool mouse_leftClick, mouse_rightClick;

	//environmental variables
	float gravity;
	float jumpPlatform_degree;

	//game variables
	sf::Clock healthUpgrade_clock;
	sf::Time healthUpgrade_timer;
	float HEALTH_UPGRADE_SPAWN_DELAY;

	sf::Clock shieldUpgrade_clock;
	sf::Time shieldUpgrade_timer;
	float SHIELD_UPGRADE_SPAWN_DELAY;

	sf::Clock speedUpgrade_clock;
	sf::Time speedUpgrade_timer;
	float SPEED_UPGRADE_SPAWN_DELAY;

	sf::Clock rifleUpgrade_clock;
	sf::Time rifleUpgrade_timer;
	float RIFLE_UPGRADE_SPAWN_DELAY;

	//data
	sf::SoundBuffer jump_buff;
	sf::Sound jump_sound;

	sf::SoundBuffer jumpPlatform_buff;
	sf::Sound jumpPlatform_sound;

	sf::SoundBuffer shoot_buff;
	sf::Sound shoot_sound;

	sf::SoundBuffer playerHurt_buff;
	sf::Sound playerHurt_sound;

	sf::SoundBuffer enemyHurt_buff;
	sf::Sound enemyHurt_sound;

	sf::SoundBuffer enemyShoot_buff;
	sf::Sound enemyShoot_sound;

	sf::SoundBuffer healthUpgrade_buff;
	sf::Sound healthUpgrade_sound;

	sf::SoundBuffer shieldUpgrade_buff;
	sf::Sound shieldUpgrade_sound;;

	sf::SoundBuffer speedUpgrade_buff;
	sf::Sound speedUpgrade_sound;

	sf::SoundBuffer rifleUpgrade_buff;
	sf::Sound rifleUpgrade_sound;

	sf::Texture bullet_tex, enemy_tex, enemyBullet_tex, healthUpgrade_tex, shieldUpgrade_tex, speedUpgrade_tex, rifleUpgrade_tex, rifleBullet_tex;
	sf::Texture jumpPlatform_tex, ground_tex, bridge_tex, platform_tex, agPlatform_tex;
};

