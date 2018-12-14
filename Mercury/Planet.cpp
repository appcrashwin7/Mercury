#include "Planet.h"

Planet::Planet(double orbit, double radius, double mass)
	:CelestialBody(orbit, radius, mass)
{
	type = CelestialBodyType::Planet;
}

Planet::~Planet()
{
}
