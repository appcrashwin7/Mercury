#include "CelestialBody.h"

CelestialBody::CelestialBody(Length radius, Mass mass, CelestialBodyType type, Orbit orb, const QString & name, Temperature temp)
	:radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(type), orbit(orb), name(name),
	surfaceTemperature(temp)
{
}

CelestialBody::CelestialBody(const CelestialBody & other, CelestialBodyType newType)
	:radius(other.radius), mass(other.mass),
	escapeVelocity(other.escapeVelocity),
	surfaceGravity(other.surfaceGravity),
	type(newType), orbit(other.orbit),
	name(other.name), surfaceTemperature(other.surfaceTemperature)
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