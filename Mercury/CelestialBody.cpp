#include "CelestialBody.h"

CelestialBody::CelestialBody(double orbit, double radius, double mass, CelestialBodyType type, CelestialBody * parent = nullptr)
	:orbitDistance(orbit), radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(CelestialBodyType::Undefided),
	Parent(parent)
{}

CelestialBody::~CelestialBody()
{
	for (size_t i = 0; i < Satellites.size(); i++)
	{
		delete Satellites[i];
	}
}

const std::vector<CelestialBody*>& CelestialBody::getSatellites() const
{
	return Satellites;
}

std::vector<CelestialBody*>& CelestialBody::getSatellites()
{
	return Satellites;
}


