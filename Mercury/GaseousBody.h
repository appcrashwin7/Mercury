#pragma once

#include "CelestialBody.h"

class GaseousBody : public CelestialBody
{
public:
	GaseousBody() = delete;
	GaseousBody(const GaseousBody & other) = default;
	GaseousBody(GaseousBody &&) = default;
	GaseousBody(CelestialBody body)
		:CelestialBody(std::move(body))
	{}
	~GaseousBody() override = default;
};