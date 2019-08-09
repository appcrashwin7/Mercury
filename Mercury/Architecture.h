#pragma once

#include "IndustryBuilding.h"

class Architecture
{
    static inline std::vector<IndustryBuilding> dt;
    static inline const QString dataFile = "Buildings.json";

public:
    Architecture() = default;
    ~Architecture() = default;

    static void load()
    {

    }

    static const& std::vector<IndustryBuilding> get()
    {
        return dt;
    }
};