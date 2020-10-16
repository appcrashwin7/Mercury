#pragma once

#include <optional>
#include <QtCore/qdatetime.h>

#include "Calc.h"

class Orbit 
{
	static void setOrbitalPeriod(Orbit& orbit, const Mass& parentMass)
	{
		auto axis = Calc::getSemiMajorAxis(orbit.apoapsis, orbit.periapsis);
		orbit.orbitalPeriod = Calc::getOrbitalPeriod(parentMass, axis);
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

	const size_t parent = 0;

	const bool isCircular = false;

	Orbit() = delete;
	Orbit(Length apo, Length per, const Mass & parentBodyMass, size_t parentID, TimeInt periapsisPassage = 0)
		:apoapsis(apo), periapsis(per), parent(parentID),
		eccentricity(Calc::getEccentric(apo, per)), isCircular(false),
		periapsisPassage(periapsisPassage), majorAxis(per + apo),
		minorAxis(apo * std::sqrt(1.0 - (std::pow(eccentricity, 2))))
	{
		setOrbitalPeriod(*this, parentBodyMass);
	}
	Orbit(Length radius, const Mass & parentBodyMass, size_t parentID, TimeInt periapsisPassage = 0)
		:apoapsis(radius), periapsis(radius), parent(parentID), 
		isCircular(true), periapsisPassage(periapsisPassage),
		majorAxis(radius), minorAxis(radius)
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