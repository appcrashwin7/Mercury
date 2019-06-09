#include "Universe.h"

Universe::Universe()
{
	using std::make_optional;

	addSystem(std::move(PlanetarySystem("Sol System")));

	auto sunMass = units::si::kilogram * 2.0e30;

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Star(CelestialBody(PhysicalProperties(units::si::meter * 6.9e8,
		sunMass, units::si::kelvin * 5800), CelestialBodyType::Star, Orbit(), "Sol")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(PhysicalProperties(units::si::meter * 2.4e6, units::si::kilogram * 3.3e23), CelestialBodyType::Planet, 
			Orbit(units::si::meter * 6.9e10, units::si::meter * 4.9e10, sunMass, 0), "Mercury")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(PhysicalProperties(units::si::meter * 6.0e6, units::si::kilogram * 4.8e24), CelestialBodyType::Planet,
			Orbit(units::si::meter * 1.08e11, units::si::meter * 1.07e11, sunMass, 0), "Venus")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(PhysicalProperties(units::si::meter * 6.3e6, units::si::kilogram * 5.9e24), CelestialBodyType::Planet, 
			Orbit(units::si::meter * 1.52e11, units::si::meter * 1.47e11, sunMass, 0), "Earth")))));

	getSystem(0).Bodies.push_back(std::move(CelestialBodyPtr(new Planet(
		CelestialBody(PhysicalProperties(units::si::meter * 1.7e6, units::si::kilogram * 7.3e22), CelestialBodyType::Planet,
	Orbit(units::si::meter * 4.0e8, units::si::meter * 3.6e8, units::si::kilogram * 7.3e22, getSystem(0).Bodies.size() - 1), "Luna")))));
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
