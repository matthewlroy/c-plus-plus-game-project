#pragma once
class HUD
{
public:
	HUD();

	void create(const std::string& path);

	void update(sf::Time deltaTime);

	sf::RectangleShape rectangle;

	int health;
	int shieldDurability;
	int rifleBullets;

	float _speedDuration;
	int speedDuration;

	bool shield;
	bool speed;

	CurrentWeapon hudWeapon;
	int kills;

	void draw(sf::RenderWindow& window);

	~HUD();

private:
	sf::Texture hud_tex;

	sf::Texture healthbar_tex;
	sf::Sprite healthbar;
	sf::RectangleShape healthbarBG;

	sf::Texture shieldbar_tex;
	sf::Sprite shieldbar;
	sf::RectangleShape shieldbarBG;

	sf::Texture speedbar_tex;
	sf::Sprite speedbar;
	sf::RectangleShape speedbarBG;

	sf::Texture gun_tex, rifle_tex;
	sf::Sprite weapon;

	sf::Texture riflebar_tex;
	sf::Sprite riflebar;
	sf::RectangleShape riflebarBG;

	sf::Font ARDARLING;
	sf::Text kills_text;
};

