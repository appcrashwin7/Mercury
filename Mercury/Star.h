#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star(const CelestialBody & body, double luminosity, float metallicity);
	~Star() override = default;

	const double luminosity;
	const float metallicity;
private:

};