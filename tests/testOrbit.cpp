#include <optional>

#include <gtest/gtest.h>
#include "Orbit.h"


TEST(Orbit_Class, DefaultConstructor)
{
	Orbit orbit;

	ASSERT_EQ(orbit.isDefault, true);
	ASSERT_EQ(orbit.apoapsis, Length());
	ASSERT_EQ(orbit.periapsis, Length());
	ASSERT_FLOAT_EQ(orbit.eccentricity, 0.0f);
	ASSERT_EQ(orbit.getOrbitalPeriod(), TimeInt());
}

TEST(Orbit_Class, properCalculations)
{
	auto sunMass = units::si::kilogram * 1.9885e30;
	Orbit earthOrb(units::si::meter * 1.521e11, units::si::meter * 1.47095e11, sunMass, 0);

	ASSERT_NEAR(earthOrb.eccentricity,/*real earth orbit eccentricity*/ 0.0167086f, 0.0002);
	auto orbitalPeriod = earthOrb.getOrbitalPeriod().value() / units::days.value();
	ASSERT_EQ(orbitalPeriod, 365);
}