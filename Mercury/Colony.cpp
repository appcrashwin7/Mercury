#include "Colony.h"

Colony::Colony(Planet & onPlanet)
	:planet(onPlanet)
{
}

const Planet & Colony::getPlanet() const
{
	return planet;
}
