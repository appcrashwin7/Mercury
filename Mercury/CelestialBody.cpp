#include "CelestialBody.h"

CelestialBody::CelestialBody(double radius, double mass, CelestialBodyType type, CelestialBody * prt, Orbit orb, const std::string & name)
	:radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(type),
	parent(prt), bodyOrbit(orb),
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
	double radiusPow = pow(radius, 3);
	double vol = 1.333 * PI_F * radiusPow;
	return (mass / vol);
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