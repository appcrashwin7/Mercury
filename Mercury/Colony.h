#pragma once

#include "Planet.h"

class Colony
{
	const Planet & planet;
public:
	Colony() = delete;
	Colony(const Colony & other);
	Colony(Planet & onPlanet);
	~Colony() = default;

	const Planet & getPlanet() const;
};