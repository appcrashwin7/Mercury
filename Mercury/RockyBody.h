#pragma once

#include "CelestialBody.h"
#include "ResourceDeposit.h"

class RockyBody : public CelestialBody
{
	const float LightElemBonus = 0.2f;
	const float HeavyElemBonus = 1.2f;

	void generateResources()
	{
		if (!resources.isNotGenerated())
		{
			return;
		}

		const double maxRes = physics.mass.value() * BODY_MASS_TO_DEPOSIT_SIZE_MULT;
		auto access = CelestialBody::getResourcesAccessByDensity(*this);

		auto densities = ResourceDeposit::getResourcesDensity();

		for (size_t i = 0; i < RESOURCES_LIST_SIZE; i++)
		{
			double normal = maxRes / densities[i];
			auto isLightElement = ResourceDeposit::isLightElem(i);
			auto am = static_cast<uint64_t>(isLightElement ? normal * LightElemBonus : normal * HeavyElemBonus);
			auto acc = (isLightElement ? access.first : access.second);

			resources[i] = std::make_pair(am, acc);
		}
	}

public:
	RockyBody() = delete;
	RockyBody(const RockyBody & other) = default;
	RockyBody(RockyBody &&) = default;
	RockyBody(CelestialBody body)
		:CelestialBody(std::move(body))
	{
		generateResources();
	}
	~RockyBody() override = default;

};