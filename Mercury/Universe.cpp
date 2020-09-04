#include "Universe.h"

PlanetarySystem & Universe::getSystem(size_t index)
{
	return systems[index];
}

PlanetarySystem* Universe::getSystem(const QString& name)
{
    auto System = std::find_if(systems.begin(), systems.end(),
        [name](const PlanetarySystem& s)
        {
            if (s.getName() == name)
            {
                return true;
            }
            return false;
        });
    if (System == systems.end())
    {
        return nullptr;
    }
    return System._Ptr;
}

const PlanetarySystem& Universe::getSystem(size_t index) const
{
	return systems[index];
}

const PlanetarySystem* Universe::getSystem(const QString& name) const
{
    auto System = std::find_if(systems.begin(), systems.end(),
        [name](const PlanetarySystem& s)
        {
            if (s.getName() == name)
            {
                return true;
            }
            return false;
        });
    if (System == systems.end())
    {
        return nullptr;
    }
    return System._Ptr;
}

void Universe::addSystem(const QString & name)
{
	systems.emplace_back(std::move(PlanetarySystem(name)));
}

void Universe::addSystem(PlanetarySystem && newSystem)
{
	systems.emplace_back(std::move(newSystem));
}

const std::vector<PlanetarySystem>& Universe::getSystems() const
{
	return systems;
}

std::vector<PlanetarySystem>& Universe::getSystems()
{
	return systems;
}

const PlanetarySystem& Universe::getLastSystem() const
{
    return systems.back();
}

PlanetarySystem& Universe::getLastSystem()
{
    return systems.back();
}
