#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star(int orbit, int radius, int mass, float luminosity, float metallicity);
	~Star();

	const float luminosity;
	const float metallicity;
private:

};