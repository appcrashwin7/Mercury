#pragma once

#include "Calc.h"

class Orbit 
{
	TimeInt orbitalPeriod = 0;
public:
	const Length apoapsis = Length(units::si::meter * 0);
	const Length periapsis = Length(units::si::meter * 0);

	const float eccentricity = 0.0f;

	const bool isZero = true;

	Orbit() = default;
	Orbit(Length apo, Length per, std::optional<Mass> parentBodyMass = std::make_optional<Mass>())
		:apoapsis(apo), periapsis(per),
		eccentricity(Calc::getEccentric(apo, per)), isZero(false)
	{
		if (parentBodyMass.has_value())
		{
			auto axis = Calc::getSemiMajorAxis(apo, per);
			orbitalPeriod = Calc::getOrbitalPeriod(parentBodyMass.value(), axis);
		}
	}
	Orbit(Length radius)
		:apoapsis(radius), periapsis(radius), isZero(false)
	{}
	Orbit(const Orbit & other) = default;
	~Orbit() = default;

	TimeInt getOrbitalPeriod() const
	{
		return orbitalPeriod;
	}
};
