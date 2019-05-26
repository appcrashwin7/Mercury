#include "Universe.h"

Universe::Universe()
{
	auto radiMult = std::pow(10, 6);

	addSystem(std::move(PlanetarySystem("Sol System")));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Star(CelestialBody(units::si::meter * 6.9 * pow(10, 8),
		units::si::kilogram * 2.0 * pow(10, 30), CelestialBodyType::Star, {}, Orbit(), "Sol", units::si::kelvin * 5800)))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(units::si::meter * (2.4 * radiMult), units::si::kilogram * 3.3 * pow(10, 23), CelestialBodyType::Planet, 0, 
			Orbit(units::si::meter * 6.9 * pow(10, 10), units::si::meter * 4.9 * pow(10, 10)), "Mercury")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(units::si::meter * 6.0 * radiMult, units::si::kilogram * 4.8 * pow(10, 24), CelestialBodyType::Planet, 0, 
			Orbit(units::si::meter * 1.08 * pow(10, 11), units::si::meter * 1.07 * pow(10, 11)), "Venus")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(units::si::meter * 6.3 * radiMult, units::si::kilogram * 5.9 * pow(10, 24), CelestialBodyType::Planet, 0, 
			Orbit(units::si::meter * 1.52 * pow(10, 11), units::si::meter * 1.47 * pow(10, 11)), "Earth")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(units::si::meter * 1.7 * radiMult, units::si::kilogram * 7.3 * pow(10, 22), CelestialBodyType::Planet,
	getSystem(0).Bodies.size() - 1, Orbit(units::si::meter * 4.0 * pow(10, 8),units::si::meter * 3.6 * pow(10, 8)), "Luna")))));
}

PlanetarySystem & Universe::getSystem(size_t index)
{
	return Systems[index];
}

void Universe::addSystem(const std::string & name)
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
