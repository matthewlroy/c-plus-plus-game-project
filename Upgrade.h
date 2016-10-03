#pragma once
enum UpgradeType { Health, Shield, Speed, RifleUp };
class Upgrade
{
public:
	Upgrade();
	Upgrade(UpgradeType upType);
	Upgrade(UpgradeType upType, sf::Vector2f size);

	UpgradeType upgradeType;

	sf::RectangleShape rectangle;
	float top, left, right, bottom;
	float width;
	float height;

	void update(sf::Time deltaTime);

	bool active;

	void draw(sf::RenderWindow& window);

	~Upgrade();

private:
	sf::Vector2f velocity;
	float floatSpeed;

	float floatHeight;
};

