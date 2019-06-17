#include "Universe.h"

Universe::Universe()
{
	using std::make_optional;
	addSystem(std::move(PlanetarySystem("Sol System")));

	constexpr auto sunMass = units::si::kilogram * 2.0e30;
	CelestialBodyFactory factory;

	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(units::si::meter * 6.9e8, sunMass, units::si::kelvin * 5800),
		Orbit(), "Sol"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(units::si::meter * 2.4e6, units::si::kilogram * 3.3e23),
		Orbit(units::si::meter * 6.9e10, units::si::meter * 4.9e10, sunMass, 0), "Mercury"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(units::si::meter * 6.0e6, units::si::kilogram * 4.8e24),
		Orbit(units::si::meter * 1.08e11, units::si::meter * 1.0e11, sunMass, 0), "Venus"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(units::si::meter * 6.3e6, units::si::kilogram * 5.9e24),
		Orbit(units::si::meter * 1.52e11, units::si::meter * 1.47e11, sunMass, 0), "Earth"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(units::si::meter * 1.7e6, units::si::kilogram * 7.3e22),
		Orbit(units::si::meter * 4.0e8, units::si::meter * 3.6e8, units::si::kilogram * 7.3e22, getLastSystem().Bodies.size() - 1), "Luna"));
}

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
