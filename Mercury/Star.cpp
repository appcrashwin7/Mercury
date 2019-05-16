#include "Star.h"

Star::Star(const CelestialBody & body, double luminosity, float metallicity)
	:CelestialBody(body, CelestialBodyType::Star), luminosity(luminosity), metallicity(metallicity)
{}
