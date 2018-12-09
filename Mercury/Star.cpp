#include "Star.h"

Star::Star(int orbit, int radius, uint64_t mass, float luminosity, float metallicity)
	:CelestialBody(orbit, radius, mass),
	luminosity(luminosity), metallicity(metallicity)
{
	type = CelestialBodyType::Star;
}

Star::~Star()
{
}
