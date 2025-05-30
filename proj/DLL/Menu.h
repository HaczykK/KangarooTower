#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define MAX_NUMBER_OF_ITEMS 4

class EXPORT_API Menu
{
public:
	Menu(float width, float height, const std::string& backgroundPath);
	~Menu();

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getPressedItem() { return selectedItemIndex; }

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
	sf::SoundBuffer selectBuffer;
	sf::SoundBuffer confirmBuffer;
	sf::Sound selectSound;
	sf::Sound confirmSound;
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};