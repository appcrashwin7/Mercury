#pragma once

#include "CelestialBody.h"
#include "ResourceDeposit.h"

class RockyBody : public CelestialBody
{
	ResourceDeposit resources;

	static void generateResources(RockyBody & currentBody)
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

		if (currentBody.resources.isNotGenerated())
		{
			const double maxRes = currentBody.physics.mass.value() * BODY_MASS_TO_DEPOSIT_SIZE_MULT;

			auto densities = ResourceDeposit::getResourcesDensity();
			auto lightElements = ResourceDeposit::getLightElementsIds();


			if (currentBody.type == CelestialBodyType::Planet)
			{
				double heavyElementsBonus = (currentBody.physics.getDensity() - MEAN_DENSITY) / 1000.0;
				double lightElementsAccessPen = heavyElementsBonus / 10.0;

				int32_t planetDensityInt = static_cast<int32_t>(currentBody.physics.getDensity());
				if (planetDensityInt >= static_cast<int32_t>(MEAN_DENSITY))
				{
					for (size_t i = 0; i < currentBody.resources.get().size(); i++)
					{
						double normal = maxRes / densities[i];
						double bonus = normal * heavyElementsBonus;

						if (isLightElem(i))
						{
							currentBody.resources.editDeposit(i).first = static_cast<uint64_t>(normal);
							currentBody.resources.editDeposit(i).second = Calc::roundToDecimalPlace<float>((1.0f - static_cast<float>(lightElementsAccessPen)), 2);
						}
						else
						{
							currentBody.resources.editDeposit(i).first = static_cast<uint64_t>(bonus);
							currentBody.resources.editDeposit(i).second = 1.0f;
						}
					}
				}
				else
				{
					double lightElementsBonus = (MEAN_DENSITY - currentBody.physics.getDensity()) / 1000.0;
					double heavyElementsAccessPen = lightElementsBonus / 10.0;

					for (size_t i = 0; i < RESOURCES_LIST_SIZE; i++)
					{
						double normal = maxRes / densities[i];
						double bonus = normal * lightElementsBonus;

						if (isLightElem(i))
						{
							currentBody.resources.editDeposit(i).first = static_cast<uint64_t>(bonus);
							currentBody.resources.editDeposit(i).second = 1.0f;
						}
						else
						{
							currentBody.resources.editDeposit(i).first = static_cast<uint64_t>(normal);
							currentBody.resources.editDeposit(i).second = Calc::roundToDecimalPlace<float>((1.0f - static_cast<float>(heavyElementsAccessPen)), 2);
						}
					}
				}
			}
		}
	}

public:
	RockyBody() = delete;
	RockyBody(const RockyBody & other) = default;
	RockyBody(RockyBody &&) = default;
	RockyBody(CelestialBody body, ResourceDeposit res = ResourceDeposit())
		:CelestialBody(std::move(body)), resources(std::move(res))
	{
		generateResources(*this);
	}
	~RockyBody() override = default;


	const ResourceDeposit & getResources() const
	{
		return resources;
	}
	ResourceDeposit & getResources()
	{
		return resources;
	}
};