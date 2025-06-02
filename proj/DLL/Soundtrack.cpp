#include "Soundtrack.h"
#include "Options.h"

Soundtrack::Soundtrack() {}

Soundtrack::~Soundtrack() 
{
    musics[0].stop();
    musics[1].stop();
}

bool Soundtrack::load(int index, const std::string& filename) 
{
    if (index < 0 || index > 1) return false;
    return musics[index].openFromFile(filename);
}

void Soundtrack::start() 
{
    currentIndex = 0;
    nextIndex = 1;
    musics[currentIndex].setVolume(Options::musicVolume);
    musics[currentIndex].setLoop(false);
    musics[currentIndex].play();
    fading = false;
}

void Soundtrack::startFadeToNext() 
{
    musics[nextIndex].setVolume(0.f);
    musics[nextIndex].setLoop(false);
    musics[nextIndex].play();
    fadeTimer = 0.f;
    fading = true;
}

void Soundtrack::update(float deltaTime) 
{
    if (!fading) 
    {
        // SprawdŸ, czy zbli¿amy siê do koñca utworu
        sf::Time remaining = musics[currentIndex].getDuration() - musics[currentIndex].getPlayingOffset();
        if (remaining.asSeconds() <= fadeDuration) 
        {
            startFadeToNext();
        }
        else 
        {
            musics[currentIndex].setVolume(Options::musicVolume); // Aktualizuj g³oœnoœæ
        }
        return;
    }

    // Crossfade
    fadeTimer += deltaTime;
    float t = fadeTimer / fadeDuration;

    if (t >= 1.f) 
    {
        musics[currentIndex].stop();
        musics[nextIndex].setVolume(Options::musicVolume);

        // Zamieñ indeksy
        std::swap(currentIndex, nextIndex);
        fading = false;
    }
    else 
    {
        musics[currentIndex].setVolume(Options::musicVolume * (1.f - t));
        musics[nextIndex].setVolume(Options::musicVolume * t);
    }
}