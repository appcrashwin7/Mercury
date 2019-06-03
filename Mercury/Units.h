#pragma once

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>

namespace boost
{
	namespace units
	{
		static const auto megawatt = units::si::watt * 1000000;
		static const auto days = units::si::second * 3600 * 24;
	};
};

namespace units = boost::units;
using Length = units::quantity<units::si::length, double>;
using Mass = units::quantity<units::si::mass, double>;
using Acceleration = units::quantity<units::si::acceleration, float>;
using Velocity = units::quantity<units::si::velocity, float>;
using Energy = units::quantity<units::si::power, uint64_t>;
using Temperature = units::quantity<units::si::temperature, int32_t>;
using EnergyD = units::quantity<units::si::power, double>;
using TimeInt = units::quantity<units::si::time, int64_t>;