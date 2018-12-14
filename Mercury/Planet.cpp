#include "Planet.h"

Planet::Planet(double orbit, double radius, double mass)
	:CelestialBody(orbit, radius, mass, CelestialBodyType::Planet, nullptr)
{

}

Planet::~Planet()
{
}
