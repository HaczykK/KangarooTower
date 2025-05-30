#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API Platform
{
private:
	sf::RectangleShape shape;

public:
	Platform(sf::Vector2f size, sf::Vector2f position);

	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
};