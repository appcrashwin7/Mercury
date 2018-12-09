#include "CelestialBody.h"

CelestialBody::CelestialBody(int orbit, int radius, uint64_t mass)
	:orbitDistance(orbit), radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(CelestialBodyType::Undefided)
{}

CelestialBody::~CelestialBody()
{
	for (size_t i = 0; i < Satellites.size(); i++)
	{
		delete Satellites[i];
	}
}

CelestialBodyType CelestialBody::getType() const
{
	return type;
}
