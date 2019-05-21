#pragma once

#include "MercurySave.h"


class GameSaver : public MercurySave
{
	const Universe * universeToSave = nullptr;
	const std::vector<Colony> * coloniesToSave = nullptr;
public:
	GameSaver() = delete;
	GameSaver(const QString & fileName)
		:MercurySave(fileName)
	{
	}
	~GameSaver() = default;

	void addUniverse(const Universe * universe)
	{
		checkIfNullptr(universe);
		universeToSave = universe;
	}
	void addColonies(const std::vector<Colony> * colonies)
	{
		checkIfNullptr(colonies);
		coloniesToSave = colonies;
	}

	void operator()()
	{
		checkIfNullptr(universeToSave);
		checkIfNullptr(coloniesToSave);

		openDB();
		createTables();
		closeDB();
	}
private:
	void createTables()
	{
		QSqlQuery createSystemsTable("CREATE TABLE IF NOT EXIST SYSTEM(ID int, CelestialObjects int)", save);
		createSystemsTable.exec();
		QSqlQuery createCelBodiesList("CREATE TABLE IF NOT EXISTS CELESTIAL_BODIES(" \
			"ID int NOT NULL, NAME text, TYPE  int NOT NULL, PARENT_ID int NOT NULL, ORBIT_APOAPSIS real NOT NULL, " \
			"ORBIT PERIAPSIS real NOT NULL, RADIUS real NOT NULL, MASS real NOT NULL);", save);
		createCelBodiesList.exec();
	}

	template<typename T>
	bool checkIfNullptr(T * ptr)
	{
		if (ptr == nullptr)
		{
			qFatal("GameSaver received nullptr!");
		}
		return false;
	}
};