#pragma once

#include <cmath>
#include <cstdint>
#include <cassert>
#include <qstring.h>

static const float GRAVITY_CONSTANT = 6.67f * static_cast<float>(pow(10, -11));
static const float PI_F = static_cast<float>(atan(1)) * 4.0f;

//represent

enum class valueRepresentation
{
	THOUSAND = 1000,
	MILLION = 1000000,
	BILLION = 1000000000
};

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

	template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
	static T roundToDecimalPlace(T value, uint64_t place)
	{
		assert((place != static_cast<uint64_t>(-1)));
		auto mult = static_cast<T>(pow(10, place));

		value *= mult;
		value = round(value);
		return (value / mult);
	}

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	static QString representValue(T value, valueRepresentation rep = valueRepresentation::MILLION)
	{
		auto ret = QString::number(value / static_cast<T>(rep));
		switch (rep)
		{
		case valueRepresentation::THOUSAND:
			ret += " k";
				break;
		case valueRepresentation::MILLION:
			ret += " mln";
				break;
		case valueRepresentation::BILLION:
			ret += " bln";
				break;
		default:
			break;
		}
		return ret;
	}
};