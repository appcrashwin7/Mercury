#pragma once

#include <QtSql/qsqldatabase>
#include <QtSql/qsqlerror>
#include <QtSql/qsqlquery>
#include <qfile>
#include <qvariant>

#include "SqlTable.h"
#include "Universe.h"

const static QString GAME_SAVE_EXTENSION = ".msave";
const static QString DB_EXTENSION = ".db";

const static QString GAME_TIME_FORMAT = "d/M/yyyy h:mm AD";

class MercurySave
{
protected:
	QSqlDatabase save = QSqlDatabase::addDatabase("QSQLITE");
	QString fileName;

public:
	MercurySave() = default;
	MercurySave(const QString & fileName)
		:fileName(fileName)
	{}
	~MercurySave()
	{
		closeDB();
	}

protected:
	void openDB()
	{
		QFile file(fileName);
		if(file.exists())
		{
			file.close();
			QFile::rename(fileName, getDbFileName());
		}
		save.setDatabaseName(getDbFileName());
		save.open();
	}
	void closeDB()
	{
		save.close();
		if (fileName.isEmpty())
			return;

		QFile::rename(getDbFileName(), fileName);
	}

public:
	static SqlTable getGameTimeTable()
	{
		return SqlTable("GAME_TIME",
			{ {"TIME", "text", true} });
	}
	static SqlTable getSystemsTable()
	{
		return SqlTable("SYSTEMS",
			{ {"ID", "int", true},
			 {"NAME", "text", false} });
	}
	static SqlTable getCelestialBodiesTable()
	{
		return SqlTable("CELESTIAL_BODIES",
			{ {"SYSTEM_ID", "int", true},
			{"ID", "int", true},
			{"NAME", "text", false},
			{"TYPE", "int", true},
			{"PARENT_ID", "int", false},
			{"ORBIT_APOAPSIS", "real", true},
			{"ORBIT_PERIAPSIS", "real", true},
			{"RADIUS", "real", true},
			{"MASS", "real", true},
			{"TEMPERATURE", "int", true}
			});
	}
	static SqlTable getColoniesTable()
	{
		return SqlTable("COLONIES",
			{ {"ID", "int", true},
			{"SYSTEM_ID", "int", true},
			{"BODY_ID", "int", true}
			});
	}

private:
	QString getDbFileName() const
	{
		auto dbNameStr = fileName.toStdString();
		dbNameStr = dbNameStr.substr(0, dbNameStr.find_last_of('.'));
		return QString::fromStdString(dbNameStr) + DB_EXTENSION;
	}
};