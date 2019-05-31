#include "Star.h"

Star::Star(const CelestialBody & body)
	:CelestialBody(body, CelestialBodyType::Star)
{}

EnergyD Star::getLuminosity()
{
	auto dRadius = std::pow(radius.value(), 2);
	auto fTemp = std::pow(surfaceTemperature.value(), 4);
	EnergyD ret(4 * PI_F * dRadius * STEFAN_BOLTZMANN_CONST * fTemp * units::si::watt);

	return ret;
}
