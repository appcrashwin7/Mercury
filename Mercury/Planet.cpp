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
	auto isLightElem = [](size_t id, std::vector<size_t> & lightElements)->bool
	{
		auto elem = std::find(lightElements.begin(), lightElements.end(), id);
		if (elem != lightElements.end())
		{
			return true;
		}
		return false;
	};
	auto roundFloatToDecimalPlace = [](float value, uint64_t place)->float
	{
		float mult = pow(10, place);

		value *= mult;
		value = round(value);
		return (value / mult);
	};

	if (custom.isNotGenerated())
	{
		const double maxRes = this->mass * 0.001 * 0.001;

		auto densities = ResourceDeposit::getResourcesDensity();
		uint64_t planetDensityInt = static_cast<uint64_t>(getDensity());
		auto planetDensity = getDensity();

		auto lightElements = ResourceDeposit::getLightElementsIds();

		if (planetDensityInt >= static_cast<uint64_t>(MEAN_DENSITY))
		{
			double heavyElementsBonus = (planetDensity - MEAN_DENSITY) / 1000.0;
			double lightElementsAccessPen = heavyElementsBonus / 10.0;

			for (size_t i = 0; i < custom.getRes().size(); i++)
			{
				double normal = maxRes / densities[i];
				double bonus = normal * heavyElementsBonus;

				if (isLightElem(i, lightElements))
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(normal);
					custom.editDeposit(i).second = roundFloatToDecimalPlace((1.0f - static_cast<float>(lightElementsAccessPen)), 2);
				}
				else
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(bonus);
					custom.editDeposit(i).second = 1.0f;
				}
			}
		}
		else
		{
			double lightElementsBonus = (MEAN_DENSITY - planetDensity) / 1000.0;
			double heavyElementsAccessPen = lightElementsBonus / 10.0;

			for (size_t i = 0; i < custom.getRes().size(); i++)
			{
				double normal = maxRes / densities[i];
				double bonus = normal * lightElementsBonus;

				if (isLightElem(i, lightElements))
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(bonus);
					custom.editDeposit(i).second = 1.0f;
				}
				else
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(normal);
					custom.editDeposit(i).second = roundFloatToDecimalPlace((1.0f - static_cast<float>(heavyElementsAccessPen)), 2);
				}
			}
		}
	}

	return custom;
}
