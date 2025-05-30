#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API Wall
{
public:
    Wall(sf::Texture* texture, float x, float width);

    void draw(sf::RenderWindow& window);
    void update(const sf::View& view); // aktualizuje pozycjê wzglêdem kamery

    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture* texture;
    float width;
    float xPos;
};