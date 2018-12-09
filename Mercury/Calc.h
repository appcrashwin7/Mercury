#pragma once

#include <cmath>
#include <cstdint>

namespace Calc
{
	static const float gravityConstant = 6.67f * pow(10, -11);
	static const float earthGravity = 9.78033;

	static float getEscapeVelocity(uint64_t mass, int radius)
	{
		mass *= 1000;
		float v = gravityConstant * mass;
		v /= radius;
		return sqrt(v);
	}

	static float getGravity(uint64_t mass, int radius)
	{
		mass *= 1000;
		float g = gravityConstant * mass;
		uint32_t rad = pow(radius, 2);
		g /= rad;
		return g /= (earthGravity);
	}
};