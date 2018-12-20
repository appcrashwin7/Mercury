#include "Star.h"

Star::Star(double radius, double mass, float luminosity, float metallicity, const std::string name)
	:CelestialBody(radius, mass, CelestialBodyType::Star, nullptr, Orbit(), name),
	luminosity(luminosity), metallicity(metallicity)
{

}

Star::Star(CelestialBody & body, float luminosity, float metallicity)
	:CelestialBody(body, CelestialBodyType::Star), luminosity(luminosity), metallicity(metallicity)
{}

Star::~Star()
{
}
