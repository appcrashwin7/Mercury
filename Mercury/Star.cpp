#include "Star.h"

Star::Star(double orbit, double radius, double mass, float luminosity, float metallicity)
	:CelestialBody(orbit, radius, mass),
	luminosity(luminosity), metallicity(metallicity)
{
	type = CelestialBodyType::Star;
}

Star::~Star()
{
}
