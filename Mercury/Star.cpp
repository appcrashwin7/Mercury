#include "Star.h"

Star::Star(double orbit, double radius, double mass, float luminosity, float metallicity)
	:CelestialBody(orbit, radius, mass, CelestialBodyType::Star, nullptr),
	luminosity(luminosity), metallicity(metallicity)
{

}

Star::~Star()
{
}
