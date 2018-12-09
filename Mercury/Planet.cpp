#include "Planet.h"

Planet::Planet(int orbit, uint64_t mass, int radius)
	:CelestialBody(orbit, radius, mass)
{
	type = CelestialBodyType::Planet;
}

Planet::~Planet()
{
}
