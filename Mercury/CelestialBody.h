#pragma once

#include <optional>

#include "Orbit.h"
#include "PhysicalProperties.h"
#include "ResourceDeposit.h"

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
protected:
	ResourceDeposit Resources = ResourceDeposit();

public:
	const CelestialBodyType type;
	const Orbit orbit;
	const PhysicalProperties physics;
	const Velocity escapeVelocity;
 	const Acceleration surfaceGravity;


	CelestialBody() = delete;
	CelestialBody(PhysicalProperties properties, CelestialBodyType type, Orbit orb = Orbit(), QString name = "");
	CelestialBody(const CelestialBody & other, CelestialBodyType newType);
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


	virtual ResourceDeposit generateResources(ResourceDeposit & custom);

	const ResourceDeposit & accessResources() const;
	ResourceDeposit & getResources();
};

using CelestialBodyPtr = std::unique_ptr<CelestialBody>;