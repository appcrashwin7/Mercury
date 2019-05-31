#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star() = delete;
	Star(Star &&) = default;
	Star(const Star & other) = delete;
	Star(const CelestialBody & body);
	~Star() override = default;

	EnergyD getLuminosity();
};