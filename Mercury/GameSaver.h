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
		saveBodies();
		closeDB();
	}
private:
	void createTables()
	{
		QSqlQuery createSystemsTable("CREATE TABLE IF NOT EXISTS SYSTEM(ID int NOT NULL, NAME text);", save);
		createSystemsTable.exec();
		QSqlQuery createCelBodiesTable("CREATE TABLE IF NOT EXISTS CELESTIAL_BODIES(SYSTEM_ID int NOT NULL, " \
			"ID int NOT NULL, NAME text, TYPE int NOT NULL, PARENT_ID int, ORBIT_APOAPSIS real NOT NULL, " \
			"ORBIT_PERIAPSIS real NOT NULL, RADIUS real NOT NULL, MASS real NOT NULL);", save);
		createCelBodiesTable.exec();
		QSqlQuery createColoniesTable("CREATE TABLE IF NOT EXISTS COLONIES("\
			"ID int NOT NULL, SYSTEM_ID int NOT NULL, BODY_ID int NOT NULL);", save);
		createColoniesTable.exec();

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
	void saveBodies()
	{
		QSqlQuery del("DELETE FROM CELESTIAL_BODIES", save);
		del.exec();
		
		for (size_t iSys = 0; iSys < universeToSave->getSystems().size(); iSys++)
		{
			for (size_t iBody = 0; iBody < universeToSave->getSystems()[iSys].Bodies.size(); iBody++)
			{
				auto body = universeToSave->getSystems()[iSys].Bodies[iBody];
				QSqlQuery insertBody;
				insertBody.prepare("INSERT INTO CELESTIAL_BODIES(SYSTEM_ID, ID, NAME, TYPE, PARENT_ID, ORBIT_APOAPSIS, ORBIT_PERIAPSIS, RADIUS, MASS) "
					"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

				insertBody.addBindValue(iSys);
				insertBody.addBindValue(iBody);
				insertBody.addBindValue(QString::fromStdString(body->name));
				insertBody.addBindValue(static_cast<uint32_t>(body->type));

				if (body->parent.has_value())
				{
					insertBody.addBindValue(body->parent.value());
				}
				else
				{
					insertBody.addBindValue(QVariant());
				}

				insertBody.addBindValue(body->bodyOrbit.apoapsis.value());
				insertBody.addBindValue(body->bodyOrbit.periapsis.value());
				insertBody.addBindValue(body->radius.value());
				insertBody.addBindValue(body->mass.value());

				insertBody.exec();
			}
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