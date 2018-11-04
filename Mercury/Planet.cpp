#include "Planet.h"

Planet::Planet(int orbit, int mass, int radius)
	:CelestialBody(orbit, radius, mass)
{
	type = CelestialBodyType::Planet;
}

Planet::~Planet()
{
}
