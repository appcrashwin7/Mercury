#pragma once

#include <cmath>
#include <cstdint>

namespace Calc
{
	static const float gravityConstant = 6.67f * pow(10, -11);
	static const float earthGravity = 9.78033;

	static float getEscapeVelocity(uint64_t mass, uint64_t radius)
	{
		double v = gravityConstant * mass;
		v /= radius;
		return sqrt(v);
	}

	static float getGravity(double mass, double radius)
	{
		double up = mass * gravityConstant;
		double down = radius * radius;

		return up / down;
	}
};