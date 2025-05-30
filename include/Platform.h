#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API Platform
{
private:
    sf::Sprite sprite;
    sf::Texture* texture; // wskaünik, nie kopia
    sf::Vector2f position;
    bool scored = false;

public:
    Platform(sf::Texture* texture, sf::Vector2f position);
    Platform(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    bool isScored() const { return scored; }
    void markScored() { scored = true; }
};