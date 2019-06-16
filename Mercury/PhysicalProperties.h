#include "Units.h"

class PhysicalProperties
{
	static void setDensity(PhysicalProperties & p)
	{
		double radiusPow = pow(p.radius.value(), 3);
		double vol = RATIO_43 * PI * radiusPow;

		p.density = (p.mass.value() / vol);
	}

	Temperature surfaceTemperature = 0;
	double density = 0;

public:
	const Length radius = 0;
	const Mass mass = 0;

	PhysicalProperties() = default;
	PhysicalProperties(Length rad, Mass m, Temperature temp = 0)
		:radius(std::move(rad)), mass(std::move(m)), surfaceTemperature(std::move(temp))
	{
		setDensity(*this);
	}
	PhysicalProperties(const PhysicalProperties & other) = default;
	PhysicalProperties(PhysicalProperties &&) = default;


	Temperature getSurfaceTemperature() const
	{
		return surfaceTemperature;
	}
	double getDensity() const
	{
		return density;
	}
};