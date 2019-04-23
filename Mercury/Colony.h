#pragma once

#include "Planet.h"

class Colony
{
	const Planet & planet;
public:
	Colony() = delete;
	Colony(Colony & other) = delete;
	Colony(Planet & onPlanet);
	~Colony() = default;

	const Planet & getPlanet() const;
};