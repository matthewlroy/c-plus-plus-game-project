#pragma once
class Menu
{
public:
	Menu();

	void create(const std::string& path);

	void update(sf::Time deltaTime);

	float top, left, right, bottom;
	float width;
	float height;
	sf::RectangleShape rectangle;
	sf::RectangleShape playButton, quitButton;

	void draw(sf::RenderWindow& window);

	~Menu();

private:
	sf::Texture menu_tex, playButton_tex, quitButton_tex;
};

