#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API Wall
{
public:
	Wall(float x, float height, float width);

	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;

private:
	sf::RectangleShape shape;
};