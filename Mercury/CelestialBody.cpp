#include "CelestialBody.h"

CelestialBody::CelestialBody(PhysicalProperties properties, CelestialBodyType type, Orbit orb, QString name)
	:physics(std::move(properties)), 
	escapeVelocity(Calc::getEscapeVelocity(physics.mass, physics.radius)),
	surfaceGravity(Calc::getGravity(physics.mass, physics.radius)),
	type(type), orbit(orb), name(std::move(name))
{
}

CelestialBody::CelestialBody(const CelestialBody & other, CelestialBodyType newType)
	:physics(other.physics), 
	escapeVelocity(other.escapeVelocity),
	surfaceGravity(other.surfaceGravity),
	type(newType), orbit(other.orbit),
	name(other.name)
{
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