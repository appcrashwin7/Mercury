#pragma once

#include <optional>

#include "Calc.h"

class Orbit 
{
	void setOrbitalPeriod(const std::optional<Mass> & parentMass)
	{
		if (parentMass.has_value())
		{
			auto axis = Calc::getSemiMajorAxis(apoapsis, periapsis);
			orbitalPeriod = Calc::getOrbitalPeriod(parentMass.value(), axis);
		}
	}

	TimeInt orbitalPeriod = 0;
	Length distanceToParent = 0;
public:
	const Length apoapsis = 0;
	const Length periapsis = 0;
	const float eccentricity = 0.0f;

	const std::optional<size_t> parent;

	const bool isDefault = true;

	Orbit() = default;
	Orbit(Length apo, Length per, const std::optional<Mass> & parentBodyMass, std::optional<size_t> parentID)
		:apoapsis(apo), periapsis(per), parent(std::move(parentID)),
		eccentricity(Calc::getEccentric(apo, per)), isDefault(false)
	{
		setOrbitalPeriod(parentBodyMass);
	}
	Orbit(Length radius, const std::optional<Mass> & parentBodyMass, std::optional<size_t> parentID)
		:apoapsis(radius), periapsis(radius), isDefault(false),
		parent(std::move(parentID))
	{
		setOrbitalPeriod(parentBodyMass);
	}
	Orbit(const Orbit & other) = default;
	Orbit(Orbit &&) = default;
	~Orbit() = default;

	TimeInt getOrbitalPeriod() const
	{
		return orbitalPeriod;
	}
};