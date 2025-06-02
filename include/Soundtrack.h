#pragma once
#include "API.h"
#include <SFML/Audio.hpp>
#include <string>

class EXPORT_API Soundtrack 
{
public:
    Soundtrack();
    ~Soundtrack();

    bool load(int index, const std::string& filename);
    void start(); // zaczyna pêtlê od pierwszego utworu
    void update(float deltaTime); // musi byæ wo³ane co klatkê

private:
    sf::Music musics[2];
    int currentIndex = 0;
    int nextIndex = 1;

    float fadeDuration = 3.0f;  // sekundy
    float fadeTimer = 0.0f;
    bool fading = false;

    void startFadeToNext();
};
