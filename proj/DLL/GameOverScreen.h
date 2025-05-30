#include "API.h"
#include <SFML/Graphics.hpp>
#include <string>

class EXPORT_API GameOverScreen 
{
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text inputText;
    std::string playerInput;
    bool enterPressed = false;

public:
    GameOverScreen(unsigned int windowWidth);

    void update(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    bool isDone() const;
    std::string getEnteredName() const;
    void setScore(int score);
    void reset();
};


