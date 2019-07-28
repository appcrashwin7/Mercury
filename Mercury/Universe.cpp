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
		Orbit(units::si::meter * 4.0e8, units::si::meter * 3.6e8, units::si::kilogram * 5.9e24, getLastSystem().Bodies.size() - 1), "Luna"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(units::kilometer * 3396.2, units::si::kilogram * 6.41e23),
		Orbit(249.2e6 * units::kilometer, 206.6e6 * units::kilometer, sunMass, 0), "Mars"));

	constexpr auto jupiterMass = units::si::kilogram * 1.8e27;
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(71492.0 * units::kilometer, jupiterMass),
		Orbit(816.6e6 * units::kilometer, 740.5e6 * units::kilometer, sunMass, 0), "Jupiter"));
	auto jupiterID = getLastSystem().Bodies.size() - 1;

	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(3643.0 * units::kilometer, units::si::kilogram * 8.9e22),
		Orbit(421700.0 * units::kilometer, jupiterMass, jupiterID), "Io"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(3122.0 * units::kilometer, units::si::kilogram * 4.8e22),
		Orbit(671034.0 * units::kilometer, jupiterMass, jupiterID), "Europa"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(5262.0 * units::kilometer, units::si::kilogram * 1.48e23),
		Orbit(1070412.0 * units::kilometer, jupiterMass, jupiterID), "Ganymede"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(4821.0 * units::kilometer, units::si::kilogram * 1.08e23),
		Orbit(1882709.0 * units::kilometer, jupiterMass, jupiterID), "Callisto"));

	constexpr auto saturnMass = units::si::kilogram * 5.6e26;
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(60268.0 * units::kilometer, saturnMass),
		Orbit(1514.5e6 * units::kilometer, 1352.6e6 * units::kilometer, sunMass, 0), "Saturn"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(2574.0 * units::kilometer, units::si::kilogram * 1.34e23),
		Orbit(1207060.0 * units::kilometer, saturnMass, getLastSystem().Bodies.size() - 1), "Titan"));

	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(25559.0 * units::kilometer, units::si::kilogram * 8.68e25),
		Orbit(units::au * 20.11, units::au * 18.33, sunMass, 0), "Uranus"));
	getLastSystem().Bodies.emplace_back(factory.createBody(PhysicalProperties(24764.0 * units::kilometer, units::si::kilogram * 1.024e26),
		Orbit(units::au * 30.33, units::au * 29.81, sunMass, 0), "Neptune"));
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
