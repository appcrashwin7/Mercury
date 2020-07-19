#pragma once

#include <vector>

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

namespace boost
{
	namespace units
	{
		static constexpr auto megawatt = units::si::watt * 1000000;
		static constexpr auto days = units::si::second * 3600 * 24;
		static constexpr auto kilometer = units::si::meter * 1000.0;
		static constexpr auto au = units::si::meter * 149597870700.0;
	};
};

namespace units = boost::units;
using Length = units::quantity<units::si::length, double>;
using Mass = units::quantity<units::si::mass, double>;
using Acceleration = units::quantity<units::si::acceleration, double>;
using Velocity = units::quantity<units::si::velocity, double>;
using Energy = units::quantity<units::si::power, int64_t>;
using Temperature = units::quantity<units::si::temperature, int32_t>;
using EnergyD = units::quantity<units::si::power, double>;
using TimeInt = units::quantity<units::si::time, int64_t>;
using Angle = units::quantity<units::si::plane_angle, double>;

constexpr int DEFAULT_UNIT_PREC = 2;

inline QString MassToText(const Mass& m, bool tons = true, bool divBy6e = true, bool exp = false, int prec = DEFAULT_UNIT_PREC)
{
	double conv = (tons ? 1.0e-3 : 1.0);
	double divEx = (divBy6e ? 1.0e-6 : 1.0);
	QString ad = (divBy6e ? " mln " : "");
	ad += (tons ? " T " : " kg ");
	double retVal = m.value() * conv * divEx;

	if (!exp)
	{
		return QString::number(retVal, 'f', prec) + ad;
	}
	return QString::number(retVal) + ad;
}
inline QString LengthToText(const Length& l, bool km = true, bool divBy6 = true, bool exp = false, int prec = DEFAULT_UNIT_PREC)
{
	double conv = (km ? 1.0e-3 : 1.0);
	double divEx = (divBy6 ? 1.0e-6 : 1.0);
	QString ad = (divBy6 ? " mln " : "");
	ad += (km ? " km " : " m ");
	double retVal = l.value() * conv * divEx;

	if (!exp)
	{
		return QString::number(retVal, 'f', prec) + ad;
	}
	return QString::number(retVal) + ad;
}
inline QString VelocityToText(const Velocity& v, bool kmh = true, bool divBy6 = true, bool exp = false, int prec = DEFAULT_UNIT_PREC)
{
	double conv = (kmh ? 1.0e-3 * 3600.0 : 1.0);
	double divEx = (divBy6 ? 1.0e-6 : 1.0);
	QString ad = (divBy6 ? " mln " : "");
	ad += (kmh ? " km/h " : " m/s ");
	double retVal = v.value() * conv * divEx;

	if (!exp)
	{
		return QString::number(retVal, 'f', prec) + ad;
	}
	return QString::number(retVal) + ad;
}
inline QString AccelerationToText(const Acceleration& a, bool kmh2 = true, bool divBy6 = true, bool exp = false, int prec = DEFAULT_UNIT_PREC)
{
	double conv = (kmh2 ? 1.0e-3 * (3600.0 * 3600.0) : 1.0);
	double divEx = (divBy6 ? 1.0e-6 : 1.0);
	QString ad = (divBy6 ? " mln " : "");
	ad += (kmh2 ? " km/h^2 " : " m/s^2 ");
	double retVal = a.value() * conv * divEx;

	if (!exp)
	{
		return QString::number(retVal, 'f', prec) + ad;
	}
	return QString::number(retVal) + ad;
}
inline QString TemperatureToText(const Temperature& t, bool c = true)
{
	int32_t nval = (c ? t.value() - 273 : t.value());
	QString ad = (c ? " C " : " K ");

	return QString::number(nval) + ad;
}

//div 0 = minutes  1 = hours, 2 = days, 3 = years 
inline QString TimeToText(const TimeInt& t, int div = 0)
{
	int divVal = 1;
	QString ad = " s";

	switch (div)
	{
	case 0:
		divVal *= 60;
		ad = " min";
		break;
	case 1:
		divVal *= 3600;
		ad = " h";
		break;
	case 2:
		divVal *= (3600 * 24);
		ad = " d";
		break;
	case 3:
		divVal *= (3600 * 24 * 365);
		ad = " y";
		break;
	}
	auto retVal = t.value() / divVal;

	return QString::number(retVal) + ad;
}