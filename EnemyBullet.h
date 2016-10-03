#pragma once
class EnemyBullet
{
public:
	EnemyBullet();
	EnemyBullet(sf::Vector2f position);
	EnemyBullet(sf::Vector2f position, sf::Vector2f velocity);

	sf::RectangleShape rectangle;
	float top, left, right, bottom;
	float width;
	float height;

	bool active;

	sf::Vector2f velocity;
	float moveSpeed;

	void update(sf::Time deltaTime);

	void draw(sf::RenderWindow& window);

	~EnemyBullet();

private:
	sf::Clock clock;
	sf::Time timer;
	float BULLET_LIFESPAN;
};

