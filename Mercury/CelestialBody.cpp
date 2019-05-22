#include "CelestialBody.h"

CelestialBody::CelestialBody(Length radius, Mass mass, CelestialBodyType type, std::optional<size_t> parent, Orbit orb, const std::string & name)
	:radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(type),
	parent(parent), bodyOrbit(orb),
	name(name)
{
}

CelestialBody::CelestialBody(const CelestialBody & other, CelestialBodyType newType)
	:radius(other.radius), mass(other.mass),
	escapeVelocity(other.escapeVelocity),
	surfaceGravity(other.surfaceGravity),
	type(newType), parent(other.parent),
	bodyOrbit(other.bodyOrbit),
	name(other.name)
{
}

double CelestialBody::getDensity() const
{
	double radiusPow = pow(radius.value(), 3);
	double vol = 1.333 * PI_F * radiusPow;
	return (mass.value() / vol);
}

ResourceDeposit CelestialBody::generateResources(ResourceDeposit & custom)
{
	custom;
	return ResourceDeposit();
}

const ResourceDeposit & CelestialBody::accessResources() const
{
	return Resources;
}

ResourceDeposit & CelestialBody::getResources()
{
	return Resources;
}