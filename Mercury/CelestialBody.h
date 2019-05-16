#pragma once

#include "Orbit.h"
#include "ResourceDeposit.h"

enum class CelestialBodyType
{
	Undefided,
	Star,
	Planet,
	GasGiant,
	Asteroid
};

static constexpr double MEAN_DENSITY = 3000.0;
static const double BODY_MASS_TO_DEPOSIT_SIZE_MULT = (1.0 / std::pow(10, 16));

class CelestialBody
{
protected:
	ResourceDeposit Resources = ResourceDeposit();
public:
	CelestialBody() = delete;
	CelestialBody(Length radius, Mass mass, CelestialBodyType type, CelestialBody * parent = nullptr, Orbit orb = Orbit(), const std::string & name = "");
	CelestialBody(const CelestialBody & other, CelestialBodyType newType);
	virtual ~CelestialBody() = default;

	std::string name;
	
	const CelestialBodyType type;
	const CelestialBody * const parent;

	const Orbit bodyOrbit;
	const Length radius;
	const Mass mass;


	const float escapeVelocity; //measured in km/s
	const Acceleration surfaceGravity;

	double getDensity() const;

	virtual ResourceDeposit generateResources(ResourceDeposit & custom);

	const ResourceDeposit & accessResources() const;
	ResourceDeposit & getResources();
};