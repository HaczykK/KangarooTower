#pragma once
#include "API.h"

class EXPORT_API Options
{
public:
	static float musicVolume;

	static void volumeUp(float step = 10.f);
	static void volumeDown(float step = 10.f);
};