#pragma once

#include <cmath>
#include <cstdint>

static const float GRAVITY_CONSTANT = 6.67f * static_cast<float>(pow(10, -11));
static const float PI_F = static_cast<float>(atan(1)) * 4.0f;


class Calc
{
public:
	Calc() = default;
	~Calc() = default;

	static float getEscapeVelocity(double mass, double radius)
	{
		double v = GRAVITY_CONSTANT * mass;
		v /= radius;
		return static_cast<float>(std::round(sqrt(v)));
	}

	static float getGravity(double mass, double radius)
	{
		double up = mass * GRAVITY_CONSTANT;
		double down = radius * radius;

		return static_cast<float>(std::round(up / down));
	}

	static float getEccentric(double apoapsis, double periapsis)
	{
		double minor_axis = (apoapsis + periapsis) / 2.0;
		double rel = (minor_axis * minor_axis) / (apoapsis * apoapsis);
		return static_cast<float>(sqrt(1.0 - rel));
	}
};