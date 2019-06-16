#pragma once

#include "Star.h"
#include "RockyBody.h"
#include "Random.h"

class CelestialBodyFactory
{
public:
	CelestialBodyPtr createBody(PhysicalProperties props, Orbit orb, QString name = "", ResourceDeposit deposit = ResourceDeposit())
	{
		if (props.mass > MIN_STAR_MASS)
		{
			return CelestialBodyPtr(new Star(GaseousBody(
				CelestialBody(std::move(props), CelestialBodyType::Star, std::move(orb), std::move(name)))));
		}
		else if (props.mass > MIN_GAS_GIANT_MASS)
		{
			return CelestialBodyPtr(new GaseousBody(CelestialBody(
				std::move(props), CelestialBodyType::GasGiant, std::move(orb), std::move(name))));
		}
		return CelestialBodyPtr(new RockyBody(CelestialBody(
			std::move(props), CelestialBodyType::Planet, std::move(orb), std::move(name)), std::move(deposit)));
	}
};