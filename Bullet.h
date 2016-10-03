#pragma once
class Bullet
{
public:
	Bullet();
	Bullet(sf::Vector2f position);
	Bullet(sf::Vector2f position, sf::Vector2f bVelocity);

	void update(sf::Time deltaTime);

	sf::RectangleShape rectangle;
	float top, left, right, bottom;
	float width;
	float height;

	sf::Vector2f velocity;
	float moveSpeed;

	void draw(sf::RenderWindow& window);

	bool active;

	~Bullet();

private:
	sf::Clock clock;
	sf::Time timer;

	float BULLET_LIFESPAN;
};

