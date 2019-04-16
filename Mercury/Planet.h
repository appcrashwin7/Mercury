#pragma once

#include "CelestialBody.h"
#include "ResourceDeposit.h"

class Planet : public CelestialBody
{
	ResourceDeposit Resources;
public:
	Planet(double radius, double mass, CelestialBody * parent, Orbit orbit, const std::string name);
	Planet(CelestialBody & body);
	~Planet();


	const ResourceDeposit & accessResources() const;
	ResourceDeposit & accessRessources();
private:

};