#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API CameraManager 
{
private:
    sf::View* view;
    float baseSpeed;
    float currentSpeed;
    bool isActive = false;

public:
    CameraManager(sf::View* gameView, float speed);

    void activate(); // aktywuje przesuwanie kamery
    bool isActivated() const;

    bool update(float dt, const sf::Vector2f& playerPos);

    sf::View& getView();

    void setSpeed(float speed);
    float getSpeed() const;
};
