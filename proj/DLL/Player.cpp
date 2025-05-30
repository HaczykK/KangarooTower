#include "Player.h"
#include <iostream>

Player::Player(const std::string& texturePath, sf::Vector2f startPos) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
    //sprite.setScale(1.4, 1.4);
}

void Player::handleInput() {
    inputDirection = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
       // sprite.setScale(1.0f, 1.0f);
        inputDirection = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //sprite.setScale(-1.0f, 1.0f);
        inputDirection = 1;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && onGround)
        jump();
}


void Player::update(float dt) {
    velocity.y += gravity * dt;

    // Przyspieszanie
    if (inputDirection != 0) {
        currentSpeedX += inputDirection * acceleration * dt;
        if (std::abs(currentSpeedX) > maxSpeed)
            currentSpeedX = inputDirection * maxSpeed;
    }
    else {
        // Hamowanie
        if (currentSpeedX > 0.f) {
            currentSpeedX -= deceleration * dt;
            if (currentSpeedX < 0.f) currentSpeedX = 0.f;
        }
        else if (currentSpeedX < 0.f) {
            currentSpeedX += deceleration * dt;
            if (currentSpeedX > 0.f) currentSpeedX = 0.f;
        }
    }

    // Dodaj odbicie tylko na chwilê
    float totalX = currentSpeedX + velocity.x;

    sprite.move(totalX * dt, velocity.y * dt);

    // T³umienie odbicia
    velocity.x *= 0.9f;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::jump() {
    velocity.y = jumpForce;
    onGround = false;
    isJump = true;
}

void Player::land(float y) {
    velocity.y = 0;
    sf::Vector2f pos = sprite.getPosition();
    pos.y = y;
    sprite.setPosition(pos);
    onGround = true;
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::Vector2f Player::getVelocity() const
{
    return velocity;
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Player::bounceFromWall(bool leftWall)
{
    if (std::abs(currentSpeedX) > 390) {
        const float bounceVelocityX = 2500.f; // poziome odbicie
        const float bounceVelocityY = -900.f; // pionowe odbicie (do góry)

        // Odbicie poziome (od lewej/prawej œciany)
        velocity.x = leftWall ? bounceVelocityX : -bounceVelocityX;

        // Odbicie pionowe
        if (onGround != true && isJump == true) {
            velocity.y = bounceVelocityY;
            onGround = false;
            isJump = false;
        }
        isJump = false;
        onGround = false; // jesteœmy w powietrzu po odbiciu
    }
}

void Player::reset(const sf::Vector2f& startPos) {
    sprite.setPosition(startPos);
    velocity = sf::Vector2f(0.f, 0.f);
}