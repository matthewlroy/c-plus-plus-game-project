#pragma once
enum EnemyFacing { eLeft, eRight };
class Enemy
{
public:
	Enemy();
	Enemy(sf::Vector2f position);

	void update(sf::Time deltaTime);

	sf::RectangleShape rectangle;

	float top, left, right, bottom;
	float width;
	float height;

	float moveSpeed;
	sf::Vector2f velocity;

	bool active;

	void draw(sf::RenderWindow& window);

	EnemyFacing enemyFacing;

	sf::Clock enemyBullet_clock;
	sf::Time enemyBullet_timer;
	float ENEMY_BULLET_SHOOT_DELAY;

	~Enemy();
};

