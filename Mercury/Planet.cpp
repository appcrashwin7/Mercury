#include "Planet.h"

Planet::Planet(double radius, double mass, CelestialBody * parent, Orbit orbit)
	:CelestialBody(radius, mass, CelestialBodyType::Planet, parent, orbit)
{}

Planet::Planet(CelestialBody & body)
	:CelestialBody(body, CelestialBodyType::Planet)
{}

Planet::~Planet()
{
}
