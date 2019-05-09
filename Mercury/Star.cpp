#include "Star.h"

Star::Star(double radius, double mass, double luminosity, float metallicity, const std::string & name)
	:CelestialBody(radius, mass, CelestialBodyType::Star, nullptr, Orbit(), name),
	luminosity(luminosity), metallicity(metallicity)
{

}

Star::Star(CelestialBody & body, double luminosity, float metallicity)
	:CelestialBody(body, CelestialBodyType::Star), luminosity(luminosity), metallicity(metallicity)
{}

Star::~Star()
{
}
