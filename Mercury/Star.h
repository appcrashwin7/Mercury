#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star(double orbit, double radius, double mass, float luminosity, float metallicity);
	~Star();

	const float luminosity;
	const float metallicity;
private:

};