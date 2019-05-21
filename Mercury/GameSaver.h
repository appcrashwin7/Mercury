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
		saveSystems();
		closeDB();
	}
private:
	void createTables()
	{
		QSqlQuery createSystemsTable("CREATE TABLE IF NOT EXISTS SYSTEM(ID int NOT NULL, NAME text);", save);
		createSystemsTable.exec();
		QSqlQuery createCelBodiesList("CREATE TABLE IF NOT EXISTS CELESTIAL_BODIES(SYSTEM_ID int NOT NULL, " \
			"ID int NOT NULL, NAME text, TYPE int NOT NULL, PARENT_ID int NOT NULL, ORBIT_APOAPSIS real NOT NULL, " \
			"ORBIT_PERIAPSIS real NOT NULL, RADIUS real NOT NULL, MASS real NOT NULL);", save);
		createCelBodiesList.exec();
	}

	void saveSystems()
	{
		QSqlQuery del("DELETE FROM SYSTEM", save);
		del.exec();
		for (size_t i = 0; i < universeToSave->getSystems().size(); i++)
		{
			QSqlQuery insert("INSERT INTO SYSTEM VALUES (" + QString::number(i) + "," + "'" +
				QString::fromStdString(universeToSave->getSystems()[i].name) + "'" +");", save);
			insert.exec();
		}
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