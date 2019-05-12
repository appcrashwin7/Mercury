#pragma once

#include "CelestialBody.h"
#include "ResourceDeposit.h"

class Planet : public CelestialBody
{
public:
	Planet() = delete;
	Planet(double radius, double mass, CelestialBody * parent, Orbit orbit, const std::string & name, ResourceDeposit res = ResourceDeposit());
	Planet(const CelestialBody & body, ResourceDeposit res = ResourceDeposit());
	~Planet() override = default;

private:
	ResourceDeposit generateResources(ResourceDeposit & custom) override;
};