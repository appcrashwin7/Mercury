#pragma once

#include <cmath>
#include <cstdint>

namespace Calc
{
	static const float gravityConstant = 6.67f * pow(10, -11);
	static const float earthGravity = 9.78033;

	static float getEscapeVelocity(uint64_t mass, int radius)
	{
		double v = gravityConstant * mass;
		v /= radius;
		return sqrt(v);
	}

	static float getGravity(uint64_t mass, int radius)
	{
		double up = gravityConstant * mass;
		radius *= 1000;
		uint64_t rad = radius * radius;
		return up / rad;
	}
};