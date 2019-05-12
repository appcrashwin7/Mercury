#include "Universe.h"

Universe::Universe()
{
	addSystem(PlanetarySystem("Sol System"));
	getSystem(0).Bodies.push_back(new Star(6.9 * pow(10, 8), 2.0 * pow(10, 30), 3.75 * pow(10, 28), 0.0122f, "Sol"));
	getSystem(0).Bodies.push_back(new Planet(
		CelestialBody(2.4 * pow(10, 6), 3.3 * pow(10, 23), CelestialBodyType::Planet, getSystem(0).Bodies.front(), Orbit(6.9 * pow(10, 10), 4.9 * pow(10, 10)), "Mercury")));
	getSystem(0).Bodies.push_back(new Planet(
		CelestialBody(6.0 * pow(10, 6), 4.8 * pow(10, 24), CelestialBodyType::Planet, getSystem(0).Bodies.front(), Orbit(1.08 * pow(10, 11), 1.07 * pow(10, 11)), "Venus")));
	getSystem(0).Bodies.push_back(new Planet(
		CelestialBody(6.3 * pow(10, 6), 5.9 * pow(10, 24), CelestialBodyType::Planet, getSystem(0).Bodies.front(), Orbit(1.52 * pow(10, 11), 1.47 * pow(10, 11)), "Earth")));
	getSystem(0).Bodies.push_back(new Planet(CelestialBody(1.7 * pow(10, 6), 7.3 * pow(10, 22), CelestialBodyType::Planet,
	getSystem(0).Bodies.back(), Orbit(4 * pow(10, 8), 3.6 * pow(10, 8)), "Luna")));
}

PlanetarySystem & Universe::getSystem(size_t index)
{
	return Systems[index];
}

void Universe::addSystem(PlanetarySystem & newSystem)
{
	Systems.push_back(newSystem);
}

void Universe::addSystem(PlanetarySystem && newSystem)
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
