#include "Planet.h"

Planet::Planet(const CelestialBody & body, ResourceDeposit res)
	:CelestialBody(body, CelestialBodyType::Planet)
{
	Resources.replace(generateResources(res));
}

ResourceDeposit Planet::generateResources(ResourceDeposit & custom)
{
	auto isLightElem = [](size_t id)->bool
	{
		auto lightElements = ResourceDeposit::getLightElementsIds();

		auto elem = std::find(lightElements.begin(), lightElements.end(), id);
		if (elem != lightElements.end())
		{
			return true;
		}
		return false;
	};

	if (custom.isNotGenerated())
	{
		const double maxRes = this->mass.value() * BODY_MASS_TO_DEPOSIT_SIZE_MULT;

		auto densities = ResourceDeposit::getResourcesDensity();
		auto planetDensityInt = static_cast<uint64_t>(getDensity());
		auto planetDensity = getDensity();

		auto lightElements = ResourceDeposit::getLightElementsIds();

		if (planetDensityInt >= static_cast<uint64_t>(MEAN_DENSITY))
		{
			double heavyElementsBonus = (planetDensity - MEAN_DENSITY) / 1000.0;
			double lightElementsAccessPen = heavyElementsBonus / 10.0;

			for (size_t i = 0; i < custom.get().size(); i++)
			{
				double normal = maxRes / densities[i];
				double bonus = normal * heavyElementsBonus;

				if (isLightElem(i))
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(normal);
					custom.editDeposit(i).second = Calc::roundToDecimalPlace<float>((1.0f - static_cast<float>(lightElementsAccessPen)), 2);
				}
				else
				{
					if (i == 12)
					{
						custom.accessDeposit(i);
					}

					custom.editDeposit(i).first = static_cast<uint64_t>(bonus);
					custom.editDeposit(i).second = 1.0f;
				}
			}
		}
		else
		{
			double lightElementsBonus = (MEAN_DENSITY - planetDensity) / 1000.0;
			double heavyElementsAccessPen = lightElementsBonus / 10.0;

			for (size_t i = 0; i < custom.get().size(); i++)
			{
				double normal = maxRes / densities[i];
				double bonus = normal * lightElementsBonus;

				if (isLightElem(i))
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(bonus);
					custom.editDeposit(i).second = 1.0f;
				}
				else
				{
					custom.editDeposit(i).first = static_cast<uint64_t>(normal);
					custom.editDeposit(i).second = Calc::roundToDecimalPlace<float>((1.0f - static_cast<float>(heavyElementsAccessPen)), 2);
				}
			}
		}
	}

	return custom;
}
