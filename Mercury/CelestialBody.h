#pragma once

#include <optional>

#include "Orbit.h"
#include "PhysicalProperties.h"

enum class CelestialBodyType
{
	Star,
	Planet,
	GasGiant,
	Asteroid
};

static constexpr double MEAN_DENSITY = 3000.0;
static constexpr double BODY_MASS_TO_DEPOSIT_SIZE_MULT = 1e-16;

class CelestialBody
{

	QString name;
public:
	const CelestialBodyType type;
	const Orbit orbit;
	const PhysicalProperties physics;
	const Velocity escapeVelocity;
 	const Acceleration surfaceGravity;


	CelestialBody() = delete;
	CelestialBody(CelestialBody &&) = default;
	CelestialBody(const CelestialBody & other) = default;
	CelestialBody(PhysicalProperties properties, CelestialBodyType type, Orbit orb = Orbit(), QString name = "")
		:physics(std::move(properties)),
		escapeVelocity(Calc::getEscapeVelocity(physics.mass, physics.radius)),
		surfaceGravity(Calc::getGravity(physics.mass, physics.radius)),
		type(type), orbit(orb), name(std::move(name))
	{
	}
	CelestialBody(const CelestialBody & other, CelestialBodyType newType)
		:physics(other.physics),
		escapeVelocity(other.escapeVelocity),
		surfaceGravity(other.surfaceGravity),
		type(newType), orbit(other.orbit),
		name(other.name)
	{
	}
	virtual ~CelestialBody() = default;


	void setName(QString newName)
	{
		name = std::move(newName);
	}
	const QString & getName() const
	{
		return name;
	}


	Velocity getEscapeVelocity() const
	{
		return escapeVelocity;
	}
	Acceleration getSurfaceGravity() const
	{
		return surfaceGravity;
	}
};

using CelestialBodyPtr = std::unique_ptr<CelestialBody>;