#pragma once

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
using Acceleration = units::quantity<units::si::acceleration, float>;
using Velocity = units::quantity<units::si::velocity, float>;
using Energy = units::quantity<units::si::power, int64_t>;
using Temperature = units::quantity<units::si::temperature, int32_t>;
using EnergyD = units::quantity<units::si::power, double>;
using TimeInt = units::quantity<units::si::time, int64_t>;