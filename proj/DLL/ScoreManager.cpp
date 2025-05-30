#include "ScoreManager.h"
#include <fstream>
#include <iostream>

ScoreManager::ScoreManager() : score(-1), lastScoredY(600.f) {
    if (!font.loadFromFile("NoctraDrip-OutlineMelt.ttf")) {
        std::cerr << "Nie uda³o siê za³adowaæ czcionki!" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(10.f, 10.f);
}

//Funkcja ktora resetuje wynik przy kolejnym podejsciu 

void ScoreManager::reset() {
    score = -1;
    lastScoredY = 600.f;
}

int ScoreManager::getScore() const {
    return score;
}

//Wynik podczas gry 

void ScoreManager::updateScoreIfNeeded(Player& player, Platform& platform, CameraManager& camera) {
    float platformY = platform.getPosition().y;

    // L¹dowanie
    if (player.getBounds().intersects(platform.getBounds()) &&
        player.getVelocity().y > 0 &&
        player.getPosition().y + player.getBounds().height <= platformY + 10.f)
    {
        player.land(platformY - player.getBounds().height);
        if (!platform.isScored()) {
            score++;
            if (score >= 20) {
                float speed = 100.f + (score - 20) * 1.f;
                camera.setSpeed(speed);
            }
            platform.markScored();
            lastScoredY = platformY;
        }
        return;
    }

    // Przeskoczenie
    if (!platform.isScored() &&
        platformY < lastScoredY &&
        player.getPosition().y + player.getBounds().height < platformY)
    {
        score++;
        if (score >= 20) {
            float speed = 100.f + (score - 20) * 1.f;
            camera.setSpeed(speed);
        }
        platform.markScored();
        lastScoredY = platformY;
    }
}

void ScoreManager::draw(sf::RenderWindow& window, const sf::View& view) {
    scoreText.setString("Score: " + std::to_string(score));
    window.setView(window.getDefaultView());
    window.draw(scoreText);
    window.setView(view);
}

//Zapis do pliku

void ScoreManager::saveScoreToFile(const std::string& nick) {
    std::ofstream file("scores.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Nie uda³o siê otworzyæ pliku do zapisu!" << std::endl;
        return;
    }
    file << nick << " " << score << "\n";
    file.close();
}

//Odczyt z pliku

void ScoreManager::loadScoresFromFile() {
    std::ifstream file("scores.txt");
    if (!file.is_open()) {
        std::cerr << "Brak pliku scores.txt" << std::endl;
        return;
    }

    std::string name;
    int s;
    while (file >> name >> s) {
        std::cout << name << ": " << s << std::endl;
    }
    file.close();
}