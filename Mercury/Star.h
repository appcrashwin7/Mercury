#pragma once

#include "GaseousBody.h"

class Star : public GaseousBody
{
	static void calcLuminosity(Star & currentStar)
	{
		auto dRadius = std::pow(currentStar.physics.radius.value(), 2);
		auto fTemp = std::pow(currentStar.physics.getSurfaceTemperature().value(), 4);
		currentStar.luminosity = 4 * PI_F * dRadius * STEFAN_BOLTZMANN_CONST * fTemp * units::si::watt;
	}

	EnergyD luminosity;
public:
	Star() = delete;
	Star(Star &&) = default;
	Star(const Star & other) = default;
	Star(GaseousBody body)
		:GaseousBody(std::move(body))
	{
		calcLuminosity(*this);
	}
	~Star() override = default;

	EnergyD getLuminosity() const
	{
		return luminosity;
	}
};