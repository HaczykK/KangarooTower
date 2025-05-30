#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API Player
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool onGround = false;

    const float gravity = 1000.0f;
    const float jumpForce = -600.0f;
    const float moveSpeed = 250.0f;

public:
    Player(const std::string& texturePath, sf::Vector2f startPos);

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void jump();
    void land(float y);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2f getVelocity() const;
};

