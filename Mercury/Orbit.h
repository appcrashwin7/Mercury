#pragma once

#include <optional>
#include <QtCore/qdatetime.h>

#include "Calc.h"

class Orbit 
{
	static void setOrbitalPeriod(Orbit & orbit, const std::optional<Mass> & parentMass)
	{
		if (parentMass.has_value())
		{
			auto axis = Calc::getSemiMajorAxis(orbit.apoapsis, orbit.periapsis);
			orbit.orbitalPeriod = Calc::getOrbitalPeriod(parentMass.value(), axis);
		}
	}

	TimeInt orbitalPeriod = 0;
	Length distanceToParent = 0;
	const TimeInt periapsisPassage = 0;
public:
	const Length apoapsis = 0;
	const Length periapsis = 0;
	const float eccentricity = 0.0f;

	const Length majorAxis = 0;
	const Length minorAxis = 0;

	const std::optional<size_t> parent;

	const bool isDefault = true;
	const bool isCircular = false;

	Orbit() = default;
	Orbit(Length apo, Length per, const std::optional<Mass> & parentBodyMass, std::optional<size_t> parentID, TimeInt periapsisPassage = 0)
		:apoapsis(apo), periapsis(per), parent(std::move(parentID)),
		eccentricity(Calc::getEccentric(apo, per)), isDefault(false),
		isCircular(false), periapsisPassage(periapsisPassage), majorAxis(per + apo),
		minorAxis(apo * std::sqrt(1.0 - (std::pow(eccentricity, 2))))
	{
		setOrbitalPeriod(*this, parentBodyMass);
	}
	Orbit(Length radius, const std::optional<Mass> & parentBodyMass, std::optional<size_t> parentID, TimeInt periapsisPassage = 0)
		:apoapsis(radius), periapsis(radius), isDefault(false),
		parent(std::move(parentID)), isCircular(true), periapsisPassage(periapsisPassage)
	{
		setOrbitalPeriod(*this, parentBodyMass);
	}
	Orbit(const Orbit & other) = default;
	Orbit(Orbit &&) = default;
	~Orbit() = default;

	TimeInt getOrbitalPeriod() const
	{
		return orbitalPeriod;
	}
	Angle getMeanMotion() const
	{
		return Angle(((2.0 * PI) / orbitalPeriod.value()) * units::si::radians);
	}
	Angle getMeanAnomaly(const QDateTime & currentTime) const
	{
		TimeInt t = currentTime.toTime_t() * units::si::seconds;
		return Angle((getMeanMotion().value() * (t - periapsisPassage).value()) * units::si::radian);
	}
};