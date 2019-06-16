#pragma once

#include "GaseousBody.h"

static constexpr Mass SOL_MASS = 1.9885e30 * units::si::kilogram;
static constexpr Length SOL_RADIUS = 695700.0 * units::kilometer;
static constexpr Temperature SOL_SURF_TEMPERATURE = 5800 * units::si::kelvin;

static constexpr Mass MIN_STAR_MASS = SOL_MASS * 0.1;
static constexpr Length MIN_STAR_RADIUS = SOL_RADIUS * 0.12;

static constexpr Mass MAX_STAR_MASS = SOL_MASS * 2.1;
static constexpr Length MAX_STAR_RADIUS = SOL_RADIUS * 1.8;

class Star : public GaseousBody
{
	static void calcLuminosity(Star & currentStar)
	{
		auto dRadius = std::pow(currentStar.physics.radius.value(), 2);
		auto fTemp = std::pow(currentStar.physics.getSurfaceTemperature().value(), 4);
		currentStar.luminosity = 4 * PI * dRadius * STEFAN_BOLTZMANN_CONST * fTemp * units::si::watt;
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


	static Temperature getEffectiveTemperature(Mass mass)
	{
		auto powedSolMass = std::pow(SOL_MASS.value(), 2.5);
		auto powedMass = std::pow(mass.value(), 2.5);
		auto massRel = powedMass / powedSolMass;

		auto powedSolTemp = std::pow(SOL_SURF_TEMPERATURE.value(), 4.0);
		auto massTemp = massRel * powedSolTemp;
		
		return Temperature(std::pow(massTemp, 1.0 / 4.0) * units::si::kelvin);
	}
};