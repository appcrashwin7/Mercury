#include "CelestialBody.h"

CelestialBody::CelestialBody(double radius, double mass, CelestialBodyType type, CelestialBody * prt = nullptr, Orbit orb = Orbit(), const std::string name = "")
	:radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(type),
	parent(parent), bodyOrbit(orb),
	name(name)
{

}

CelestialBody::CelestialBody(CelestialBody & other, CelestialBodyType newType)
	:radius(other.radius), mass(other.mass),
	escapeVelocity(other.escapeVelocity),
	surfaceGravity(other.surfaceGravity),
	type(newType), parent(other.parent),
	bodyOrbit(other.bodyOrbit),
	name(other.name)
{
}

CelestialBody::~CelestialBody()
{
}