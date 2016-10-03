#pragma once
enum PlayerFacing { Left, Right };
class Player
{
public:
	Player();

	void create(const std::string& path);
	
	void update(sf::Time deltaTime);

	void draw(sf::RenderWindow& window);

	sf::Time speedDuration_timer;
	void resetSpeedDuration();

	float top, left, right, bottom;
	sf::RectangleShape rectangle;
	sf::Vector2f velocity;
	float moveSpeed, jumpSpeed;
	bool isJumping;
	bool agCollision;

	sf::RectangleShape shield_rect, speed_rect;

	float width;
	float height;

	bool bottomCollision;
	float bottomCollisionLocation;
	bool rightCollision;
	float rightCollisionLocation;
	bool leftCollision;
	float leftCollisionLocation;

	int health;
	int shieldDurability;
	int rifleBullets;

	bool shield;
	bool speed;

	PlayerFacing playerFacing;

	~Player();

private:
	sf::Texture player_tex;
	sf::Texture shield_tex, speed_tex;

	sf::Clock speedDuration_clock;
	float SPEED_DURATION;
};

