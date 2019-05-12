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

class CelestialBody
{
protected:
	ResourceDeposit Resources = ResourceDeposit();
public:
	CelestialBody() = delete;
	CelestialBody(double radius, double mass, CelestialBodyType type, CelestialBody * parent = nullptr, Orbit orb = Orbit(), const std::string & name = "");
	CelestialBody(const CelestialBody & other, CelestialBodyType newType);
	virtual ~CelestialBody() = default;

	std::string name;
	
	const CelestialBodyType type;
	const CelestialBody * const parent;

	const Orbit bodyOrbit;//measured in km
	const double radius;// measured in m
	const double mass;//measured in kg

	const float escapeVelocity; //measured in km/s
	const float surfaceGravity; //in m/s^2

	double getDensity() const;

	virtual ResourceDeposit generateResources(ResourceDeposit & custom);

	const ResourceDeposit & accessResources() const;
	ResourceDeposit & getResources();
};