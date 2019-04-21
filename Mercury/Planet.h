#pragma once

#include "CelestialBody.h"
#include "ResourceDeposit.h"

class Planet : public CelestialBody
{
	ResourceDeposit Resources;
public:
	Planet() = delete;
	Planet(double radius, double mass, CelestialBody * parent, Orbit orbit, const std::string name, ResourceDeposit res = ResourceDeposit());
	Planet(CelestialBody & body, ResourceDeposit res = ResourceDeposit());
	~Planet();


	const ResourceDeposit & accessResources() const;
	ResourceDeposit & getRessources();
private:
	ResourceDeposit generateResources(ResourceDeposit & custom);
};