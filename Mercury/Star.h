#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star(int orbit, int radius, uint64_t mass, float luminosity, float metallicity);
	~Star();

	const float luminosity;
	const float metallicity;
private:

};