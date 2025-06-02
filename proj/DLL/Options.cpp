#include "Options.h"
#include <algorithm>

float Options::musicVolume = 100.f;

void Options::volumeUp(float step) 
{
    musicVolume = std::min(100.f, musicVolume + step);
}

void Options::volumeDown(float step) 
{
    musicVolume = std::max(0.f, musicVolume - step);
}