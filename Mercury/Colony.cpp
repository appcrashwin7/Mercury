#include "Colony.h"

Colony::Colony(const Colony & other)
	:planet(other.planet)
{
}

Colony::Colony(Planet & onPlanet)
	:planet(onPlanet)
{
}

const Planet & Colony::getPlanet() const
{
	return planet;
}
