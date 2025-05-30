#include "Platform.h"

Platform::Platform(sf::Texture* tex, sf::Vector2f pos) 
{
    texture = tex;
    sprite.setTexture(*texture);
    sprite.setPosition(pos);
    position = pos;
}

Platform::Platform(sf::Texture* tex, sf::Vector2f pos, sf::Vector2f size)
{
    texture = tex;
    sprite.setTexture(*texture);
    sprite.setPosition(pos);

    // Skalowanie tekstury do po¿¹danego rozmiaru
    sf::Vector2u textureSize = texture->getSize();
    sprite.setScale(size.x / textureSize.x, size.y / textureSize.y);

    position = pos;
}

void Platform::draw(sf::RenderWindow& window) 
{
    window.draw(sprite);
}

sf::FloatRect Platform::getBounds() const 
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Platform::getPosition() const 
{
    return sprite.getPosition();
}