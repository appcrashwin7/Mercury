#pragma once

#include "CelestialBody.h"

static constexpr Mass MIN_GAS_GIANT_MASS = 5.972e25 * units::si::kilogram;
static constexpr double MAX_GAS_GIANT_DENSITY = 1700.0;

class GaseousBody : public CelestialBody
{
public:
	GaseousBody() = delete;
	GaseousBody(const GaseousBody & other) = default;
	GaseousBody(GaseousBody &&) = default;
	GaseousBody(CelestialBody body)
		:CelestialBody(std::move(body))
	{}
	~GaseousBody() override = default;
};