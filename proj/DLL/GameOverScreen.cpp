#include "GameOverScreen.h"
#include <iostream>
#include <sstream>

GameOverScreen::GameOverScreen(unsigned int windowWidth) 
{
    if (!font.loadFromFile("NoctraDrip-OutlineMelt.ttf")) 
    {
        std::cerr << "Nie uda³o siê za³adowaæ czcionki!" << std::endl;
    }

    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(windowWidth / 2.f - 150.f, 100.f);

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth / 2.f - 100.f, 180.f);

    inputText.setFont(font);
    inputText.setCharacterSize(25);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(windowWidth / 2.f - 200.f, 250.f);
    inputText.setString("Wpisz nick: ");
}

void GameOverScreen::setScore(int score) 
{
    std::stringstream ss;
    ss << "Twoj wynik: " << score;
    scoreText.setString(ss.str());
}

void GameOverScreen::update(const sf::Event& event) 
{
    if (enterPressed) return;

    if (event.type == sf::Event::TextEntered) 
    {
        if (event.text.unicode == '\b' && !playerInput.empty()) 
        {
            playerInput.pop_back();
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') 
        {
            enterPressed = true;
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) 
        {
            playerInput += static_cast<char>(event.text.unicode);
        }

        inputText.setString("Wpisz nick: " + playerInput);
    }
}

void GameOverScreen::draw(sf::RenderWindow& window) 
{
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(inputText);
}

bool GameOverScreen::isDone() const 
{
    return enterPressed;
}

std::string GameOverScreen::getEnteredName() const 
{
    return playerInput.empty() ? "Gracz" : playerInput;
}

void GameOverScreen::reset() 
{
    enterPressed = false;
    playerInput.clear();
    inputText.setString("Wpisz nick i nacisnij Enter: ");
}

