#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star(double radius, double mass, double luminosity, float metallicity, const std::string & name);
	Star(CelestialBody &body, double luminosity, float metallicity);
	~Star();

	const double luminosity;
	const float metallicity;
private:

};