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
    bool isJump = false;


    const float gravity = 1000.0f;
    const float jumpForce = -600.0f;
    //const float moveSpeed = 50.0f;
    float currentSpeedX = 0.f;
    const float acceleration = 800.f;
    const float maxSpeed = 400.f;
    const float deceleration = 800.f;
    int moveDirection = 0; // -1 = lewo, 1 = prawo, 0 = nic
    int inputDirection = 0; // -1 = A, 1 = D, 0 = nic

public:
    Player(const std::string& texturePath, sf::Vector2f startPos);

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void jump();
    void land(float y);

    void bounceFromWall(bool leftWall);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2f getVelocity() const;
    sf::Vector2f inputVelocity;

    void reset(const sf::Vector2f& startPos);
};