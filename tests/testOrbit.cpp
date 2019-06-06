#include <optional>

#include <gtest/gtest.h>
#include "Orbit.h"


TEST(Orbit_Class, DefaultConstructor)
{
	Orbit orbit;

	ASSERT_EQ(orbit.isZero, true);
	ASSERT_EQ(orbit.apoapsis, Length());
	ASSERT_EQ(orbit.periapsis, Length());
}