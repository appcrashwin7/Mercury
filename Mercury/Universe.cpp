#include "Universe.h"

PlanetarySystem & Universe::getSystem(size_t index)
{
	return Systems[index];
}

void Universe::addSystem(const QString & name)
{
	Systems.emplace_back(std::move(PlanetarySystem(name)));
}

void Universe::addSystem(PlanetarySystem && newSystem)
{
	Systems.emplace_back(std::move(newSystem));
}

const std::vector<PlanetarySystem>& Universe::getSystems() const
{
	return Systems;
}

std::vector<PlanetarySystem>& Universe::getSystems()
{
	return Systems;
}
