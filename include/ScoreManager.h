#pragma once
#include "API.h"
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"
#include "CameraManager.h"
#include <string>

class EXPORT_API ScoreManager {
private:
    int score;
    float lastScoredY;
    sf::Font font;
    sf::Text scoreText;

public:
    ScoreManager();

    void reset();
    int getScore() const;

    // aktualizuje punkty w zale¿noœci od kolizji z platform¹
    void updateScoreIfNeeded(Player& player, Platform& platform, CameraManager& camera);

    void draw(sf::RenderWindow& window, const sf::View& view);

    void saveScoreToFile(const std::string& nick);
    void loadScoresFromFile(); // mo¿esz sobie to rozbudowaæ np. do wyœwietlania

};
