#include "Universe.h"

Universe::Universe()
{
}

Universe::~Universe()
{
}

PlanetarySystem & Universe::getSystem(size_t index)
{
	return Systems[index];
}

void Universe::addSystem(PlanetarySystem & newSystem)
{
	Systems.push_back(newSystem);
}

const std::vector<PlanetarySystem>& Universe::getSystems() const
{
	return Systems;
}

std::vector<PlanetarySystem>& Universe::getSystems()
{
	return Systems;
}
