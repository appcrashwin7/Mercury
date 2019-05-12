#include "Planet.h"

Planet::Planet(double radius, double mass, CelestialBody * parent, Orbit orbit, const std::string & name, ResourceDeposit res)
	:CelestialBody(radius, mass, CelestialBodyType::Planet, parent, orbit, name)
{
	Resources.replace(generateResources(res));
}

Planet::Planet(const CelestialBody & body, ResourceDeposit res)
	:CelestialBody(body, CelestialBodyType::Planet)
{
	Resources.replace(generateResources(res));
}

ResourceDeposit Planet::generateResources(ResourceDeposit & custom)
{
	if (custom.isNotGenerated())
	{
		const double maxRes = this->mass * 0.001 * 0.001;

		auto densities = ResourceDeposit::getResourcesDensity();
		
		for (size_t i = 0; i < custom.getRes().size(); i++)
		{
			custom.editDeposit(i).first = static_cast<uint64_t>(maxRes / densities[i]);
			custom.editDeposit(i).second = 1.0f;
		}
	}

	return custom;
}
