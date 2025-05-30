#include "Platform.h"

Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
    shape.setSize(size);
    shape.setFillColor(sf::Color::Black); // Mo¿na zmieniæ na teksturê
    shape.setPosition(position);
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Platform::getPosition() const {
    return shape.getPosition();
}