#pragma once

#include <cmath>
#include <cstdint>

namespace Calc
{
	static const float gravityConstant = 6.67f * pow(10, -11);

	static float getEscapeVelocity(double mass, double radius)
	{
		double v = gravityConstant * mass;
		v /= radius;
		return std::round(sqrt(v));
	}

	static float getGravity(double mass, double radius)
	{
		double up = mass * gravityConstant;
		double down = radius * radius;

		return std::round(up / down);
	}
	static float getEccentric(double apoapsis, double periapsis)
	{
		double minor_axis = (apoapsis + periapsis) / 2.0;
		double rel = (minor_axis * minor_axis) / (apoapsis * apoapsis);
		return sqrt(1.0 - rel);
	}
};