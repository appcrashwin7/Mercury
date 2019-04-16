#include "Planet.h"

Planet::Planet(double radius, double mass, CelestialBody * parent, Orbit orbit, const std::string name)
	:CelestialBody(radius, mass, CelestialBodyType::Planet, parent, orbit, name)
{}

Planet::Planet(CelestialBody & body)
	:CelestialBody(body, CelestialBodyType::Planet)
{}

Planet::~Planet()
{
}

const ResourceDeposit & Planet::accessResources() const
{
	return Resources;
}

ResourceDeposit & Planet::accessRessources()
{
	return Resources;
}
