#include "Player.h"
#include <iostream>

Player::Player(const std::string& texturePath, sf::Vector2f startPos) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setPosition(startPos);
}

void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        sprite.move(-moveSpeed * 0.016f, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        sprite.move(moveSpeed * 0.016f, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onGround)
        jump();
}

void Player::update(float dt) {
    velocity.y += gravity * dt;
    sprite.move(0, velocity.y * dt);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::jump() {
    velocity.y = jumpForce;
    onGround = false;
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

