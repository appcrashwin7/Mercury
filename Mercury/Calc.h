#pragma once

#include<cmath>

namespace Calc
{
	static const float gravityConstant = 6.67f * pow(10, -11);
	static const float earthGravity = 9.78033;

	static float getEscapeVelocity(int mass, int radius)
	{
		mass *= 1000;
		float v = gravityConstant * mass;
		v /= radius;
		return sqrt(v);
	}

	static float getGravity(int mass, int radius)
	{
		mass *= 1000;
		float g = gravityConstant * mass;
		g /= (pow(radius, 2));

		return g /= (earthGravity);
	}
};