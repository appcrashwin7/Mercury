#include "Planet.h"

Planet::Planet(double radius, double mass, CelestialBody * parent, Orbit orbit, const std::string name, ResourceDeposit res)
	:CelestialBody(radius, mass, CelestialBodyType::Planet, parent, orbit, name),
	Resources(generateResources(res))
{
}

Planet::Planet(const CelestialBody & body, ResourceDeposit res)
	:CelestialBody(body, CelestialBodyType::Planet),
	Resources(generateResources(res))
{
}

Planet::~Planet()
{
}

const ResourceDeposit & Planet::accessResources() const
{
	return Resources;
}

ResourceDeposit & Planet::getRessources()
{
	return Resources;
}

ResourceDeposit Planet::generateResources(ResourceDeposit & custom)
{
	if (custom.isNotGenerated())
	{
		const double maxRes = this->mass * 0.001 * 0.001;

		const double radiusPow = pow(radius, 3);
		const double vol = 1.333 * Calc::piF * radiusPow;
		const double density = mass / vol;
		
		for (size_t i = 0; i < custom.getRes().size(); i++)
		{
			custom.editDeposit(i).first = maxRes;
			custom.editDeposit(i).second = 1.0f;
		}
	}

	return custom;
}
