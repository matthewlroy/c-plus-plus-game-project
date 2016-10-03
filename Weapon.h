#pragma once
class Weapon
{
public:
	Weapon();

	void create(const std::string& path);

	void update(sf::Time deltaTime);

	float top, left, right, bottom;
	float width;
	float height;

	void draw(sf::RenderWindow& window);

	sf::RectangleShape rectangle;

	CurrentWeapon weaponCurrentWeapon;

	~Weapon();

private:
	sf::Texture gun_tex, rifle_tex;
};

