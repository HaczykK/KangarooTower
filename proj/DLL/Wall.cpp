#include "Wall.h"

Wall::Wall(sf::Texture* tex, float x, float width)
{
    texture = tex;
    this->width = width;
    xPos = x;

    sprite.setTexture(*texture);
    sprite.setScale(width / texture->getSize().x, 1.f);
    sprite.setPosition(x, 0.f);
}

void Wall::update(const sf::View& view)
{
    float startY = view.getCenter().y - view.getSize().y / 2.f;
    sprite.setPosition(xPos, startY);
    sprite.setScale(width / texture->getSize().x, view.getSize().y / texture->getSize().y);
}

void Wall::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Wall::getBounds() const
{
    return sprite.getGlobalBounds();
}