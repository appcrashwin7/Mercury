#pragma once

#include "CelestialBody.h"

static constexpr Mass MIN_GAS_GIANT_MASS = 5.972e25 * units::si::kilogram;
static constexpr double MAX_GAS_GIANT_DENSITY = 1700.0;

class GaseousBody : public CelestialBody
{
	const float lightElemBonus = 4.0f;
	const float heavyElemBonus = 0.2f;

	void generateResources()
	{
		if (!resources.isNotGenerated())
		{
			return;
		}

		const double maxResources = physics.mass.value() * BODY_MASS_TO_DEPOSIT_SIZE_MULT;
		auto access = getResourcesAccessByDensity(*this);

		for (size_t r_id = 0; r_id < RESOURCES_LIST_SIZE; r_id++)
		{
			double res = maxResources / ResourceDeposit::getResourcesDensity()[r_id];
			auto isLightElem = ResourceDeposit::isLightElem(r_id);

			auto am = static_cast<uint64_t>(isLightElem ? res * lightElemBonus : res * heavyElemBonus);
			auto acc = (isLightElem ? access.first : access.second);

			resources[r_id] = std::make_pair(am, acc);
		}

		return;
	}
public:
	GaseousBody() = delete;
	GaseousBody(const GaseousBody & other) = default;
	GaseousBody(GaseousBody &&) = default;
	GaseousBody(CelestialBody body)
		:CelestialBody(std::move(body))
	{}
	~GaseousBody() override = default;
};