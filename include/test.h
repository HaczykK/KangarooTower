
#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>

class EXPORT_API SimpleWindow {
public:
    SimpleWindow();
    void run();
private:
    sf::RenderWindow window;
    sf::RectangleShape rectangle;
};