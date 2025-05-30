#include "Background.h"
#include <iostream>

Background::Background(const std::string& texturePath)
{
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}

void Background::draw(sf::RenderWindow& window, const sf::View& view)
{
	sprite.setPosition(view.getCenter().x - view.getSize().x / 2.f,
		view.getCenter().y - view.getSize().y / 2.f);

	window.draw(sprite);
}