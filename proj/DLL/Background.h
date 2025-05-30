#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API Background
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Background(const std::string& texturePath);
	void draw(sf::RenderWindow& window, const sf::View& view);
};
