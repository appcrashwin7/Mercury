#pragma once

#include "MercurySave.h"


class GameSaver : public MercurySave
{
	const Universe * universeToSave;
	const std::vector<Colony> * coloniesToSave;
public:
	GameSaver() = delete;
	GameSaver(const QString & fileName)
		:MercurySave(fileName)
	{
	}
	~GameSaver() = default;

	void addUniverse(const Universe * universe)
	{
		if (universe == nullptr)
		{
			qFatal("GameSaver received nullpointer to Universe");
		}
		universeToSave = universe;
	}
	void addColonies(const std::vector<Colony> * colonies)
	{
		if (colonies == nullptr)
		{
			qFatal("GameSaver received nullpointer to vector<Colony>");
		}
		coloniesToSave = colonies;
	}

	void operator()()
	{
		openDB();
		closeDB();
	}
private:
};