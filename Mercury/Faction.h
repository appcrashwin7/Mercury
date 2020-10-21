#pragma once

#include "Colony.h"


class Faction
{
    std::vector<Colony> colonies;
public:
    Faction() = default;
    Faction(std::vector<Colony> colonies)
        :colonies(std::move(colonies))
    {};
    ~Faction() = default;

    const std::vector<Colony>& getColonies() const
    {
        return colonies;
    }
    std::vector<Colony> & getColonies()
    {
        return colonies;
    }
};