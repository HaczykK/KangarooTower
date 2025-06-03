#include "ScoreManager.h"
#include <fstream>
#include <iostream>

ScoreManager::ScoreManager() : score(-1), lastScoredY(600.f) 
{
    if (!font.loadFromFile("NoctraDrip-OutlineMelt.ttf")) 
    {
        std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10.f, 10.f);
}

//Funkcja ktora resetuje wynik przy kolejnym podejsciu 

void ScoreManager::reset() 
{
    score = -1;
    lastScoredY = 600.f;
}

int ScoreManager::getScore() const 
{
    return score;
}

//Wynik podczas gry 

void ScoreManager::updateScoreIfNeeded(Player& player, Platform& platform, CameraManager& camera) 
{
    float platformY = platform.getPosition().y;

    // L¹dowanie
    if (player.getBounds().intersects(platform.getBounds()) &&
        player.getVelocity().y > 0 &&
        player.getPosition().y + player.getBounds().height <= platformY + 10.f)
    {
        player.land(platformY - player.getBounds().height);
        if (!platform.isScored()) 
        {
            score++;
            if (score >= 20) 
            {
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
        if (score >= 20) 
        {
            float speed = 100.f + (score - 20) * 1.f;
            camera.setSpeed(speed);
        }
        platform.markScored();
        lastScoredY = platformY;
    }
}

void ScoreManager::draw(sf::RenderWindow& window, const sf::View& view) 
{
    scoreText.setString("Score: " + std::to_string(score));
    window.setView(window.getDefaultView());
    window.draw(scoreText);
    window.setView(view);
}

//Zapis do pliku

void ScoreManager::saveScoreToFile(const std::string& nick) 
{
    try {
        std::ofstream file("scores.txt", std::ios::app);
        if (!file) throw std::ios_base::failure("Nie udalo sie otworzyc pliku do zapisu.");
        file << nick << " " << score << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Blad zapisu do pliku: " << e.what() << std::endl;
    }
}

//Odczyt z pliku

std::vector<std::string> ScoreManager::getScoresAsStrings()
{
    std::vector<std::pair<std::string, int>> scores;
    try {
        std::ifstream file("scores.txt");
        if (!file) throw std::ios_base::failure("Nie udalo sie otworzyc pliku do odczytu.");

        std::string name;
        int s;
        while (file >> name >> s) {
            scores.emplace_back(name, s);
        }

        // Sortuj malej¹co po wyniku
        std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        // Przygotuj tylko top 10 wyników
        std::vector<std::string> results;
        int count = 0;
        for (const auto& entry : scores) {
            if (count++ >= 12) break;
            results.push_back(entry.first + ": " + std::to_string(entry.second));
        }
        return results;
    }
    catch (const std::exception& e) {
        return { std::string("Blad odczytu wynikow: ") + e.what() };
    }
}
