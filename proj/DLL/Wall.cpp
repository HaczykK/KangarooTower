#include "Wall.h"
#include <iostream>

Wall::Wall(float x, float height, float width)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x, 0.f);
	shape.setFillColor(sf::Color::Transparent);
}

void Wall::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::FloatRect Wall::getBounds() const
{
	return shape.getGlobalBounds();
}