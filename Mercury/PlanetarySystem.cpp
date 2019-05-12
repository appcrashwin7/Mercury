#include "PlanetarySystem.h"

PlanetarySystem::PlanetarySystem(const std::string & sysName)
	:name(sysName)
{
}

PlanetarySystem::~PlanetarySystem()
{
	for (auto body : Bodies)
	{
		delete body;
	}
}
