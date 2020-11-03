#pragma once

#include <cmath>
#include <cstdint>
#include <cassert>
#include <qstring.h>
#include <qpoint.h>

#include "Units.h"


static constexpr float GRAVITY_CONSTANT = 6.67e-11f;
static constexpr double STEFAN_BOLTZMANN_CONST = 5.670373e-8;
static constexpr double PI = 3.14159;
static constexpr double RATIO_43 = 4.0 / 3.0;


enum class valueRepresentation
{
	THOUSAND = 1000,
	MILLION = 1000000,
	BILLION = 1000000000
};

class Calc
{
	static constexpr size_t eccentricAnomalySteps = 20;
public:
	Calc() = default;
	~Calc() = default;

	//density is in kg/m^3
	inline static Length getRadius(Mass mass, double density)
	{
		auto massDensRel = (mass.value() / (density * PI * RATIO_43));
		return Length(std::pow(massDensRel, 1.0 / 3.0) * units::si::meter);
	}

	inline static Velocity getEscapeVelocity(Mass mass, Length radius)
	{
		double v = 2.0 * GRAVITY_CONSTANT * mass.value();
		v /= radius.value();
		return static_cast<Velocity>(std::round(sqrt(v)) * units::si::meters_per_second);
	}

	inline static Acceleration getGravity(Mass mass, Length radius)
	{
		double up = mass.value() * GRAVITY_CONSTANT;
		auto down = radius * radius;
		return static_cast<Acceleration>(std::round(up / down.value()) * units::si::meters_per_second_squared);
	}

	inline static Length getSemiMajorAxis(Length apoapsis, Length periapsis)
	{
		return Length((apoapsis + periapsis) / 2.0);
	}

	inline static float getEccentric(Length apoapsis, Length periapsis)
	{
		Length up(apoapsis - periapsis);
		Length down(apoapsis + periapsis);
		return (up.value() / down.value());
	}

	inline static TimeInt getOrbitalPeriod(Mass parentBodyMass, Length semiMajorAxis)
	{
		auto majorPow = std::pow(semiMajorAxis.value(), 3);
		auto gm = GRAVITY_CONSTANT * parentBodyMass.value();

		auto mjrGm = std::sqrt(majorPow) / std::sqrt(gm);
		auto ret = mjrGm * 2.0 * PI;
		return TimeInt(ret * units::si::second);
	}

	inline static QPoint getCoordsOfBody(double a, double b, double meanAnomaly)
	{
		return QPoint(
			static_cast<int>(a * std::cos(meanAnomaly)),
			static_cast<int>(b * std::sin(meanAnomaly))
		);
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

	inline static Angle getTrueAnomaly(Angle meanAnomaly, double e)
	{
		auto eccentricAnomaly = meanAnomaly;
		for (size_t i = 0; i < eccentricAnomalySteps; i++)
		{
			eccentricAnomaly = meanAnomaly + (e * sin(eccentricAnomaly.value()) * units::si::radians);
		}

		double ec = sqrt((1 + e) / (1 - e));
		return 2.0 * atan(ec * tan(eccentricAnomaly.value() / 2.0)) * units::si::radians;
	}

	inline static double getR(double semiMajorAxis, Angle trueAnomaly, double e)
	{
		return (semiMajorAxis / (1 - std::pow(e, 2)))
			/ (1.0 + (e * std::cos(trueAnomaly.value())));
	}
};