#include "CelestialBody.h"

CelestialBody::CelestialBody(double radius, double mass, CelestialBodyType type, CelestialBody * prt = nullptr, Orbit orb = Orbit())
	:radius(radius), mass(mass),
	escapeVelocity(Calc::getEscapeVelocity(mass, radius)),
	surfaceGravity(Calc::getGravity(mass, radius)),
	type(CelestialBodyType::Undefided),
	parent(parent), bodyOrbit(orb)
{

}

CelestialBody::CelestialBody(CelestialBody & other, CelestialBodyType newType)
	:radius(other.radius), mass(other.mass),
	escapeVelocity(other.escapeVelocity),
	surfaceGravity(other.surfaceGravity),
	type(newType), parent(other.parent),
	bodyOrbit(other.bodyOrbit)
{
	for (size_t i = 0; i < Satellites.size(); i++)
	{
		Satellites.push_back(other.Satellites[i]);
		other.Satellites[i] = nullptr;
	}
	other.Satellites.clear();
}

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