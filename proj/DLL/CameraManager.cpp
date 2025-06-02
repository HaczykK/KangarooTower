#include "CameraManager.h"

CameraManager::CameraManager(sf::View* gameView, float speed)
    : view(gameView), baseSpeed(speed), currentSpeed(speed)
{
}

void CameraManager::activate() 
{
    isActive = true;
}

bool CameraManager::isActivated() const 
{
    return isActive;
}

bool CameraManager::update(float dt, const sf::Vector2f& playerPos)
{
    if (!isActive) return false;

    // jeœli gracz jest wy¿ej ni¿ œrodek kamery, to przesuwamy kamerê, ale nie wyprzedzamy gracza
    float cameraY = view->getCenter().y;

    if (playerPos.y < cameraY - 100.f) 
    {
        view->setCenter(view->getCenter().x, playerPos.y + 100.f);
    }
    else 
    {
        view->move(0, -currentSpeed * dt); // goni gracza
    }

    float cameraBottom = view->getCenter().y + view->getSize().y / 2;
    return playerPos.y > cameraBottom;
}

sf::View& CameraManager::getView()
{
    return *view;
}

void CameraManager::setSpeed(float speed) 
{
    currentSpeed = speed;
}

float CameraManager::getSpeed() const 
{
    return currentSpeed;
}
