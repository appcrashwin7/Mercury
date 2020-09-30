#pragma once

#include <qstring.h>

#include "Colony.h"


class Faction
{
    QString name;

    std::vector<Colony> colonies;
public:
    Faction() = default;
    ~Faction() = default;

    void setName(QString newName)
    {
        name = newName;
    }
    QString getName()
    {
        return name;
    }

    const std::vector<Colony>& getColonies() const
    {
        return colonies;
    }
};