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
			{ std::make_tuple("TIME", "text", true) });
	}
	static SqlTable getSystemsTable()
	{
		return SqlTable("SYSTEMS",
			{ std::make_tuple("ID", "int", true),
			std::make_tuple("NAME", "text", false) });
	}

private:
	QString getDbFileName() const
	{
		auto dbNameStr = fileName.toStdString();
		dbNameStr = dbNameStr.substr(0, dbNameStr.find_last_of('.'));
		return QString::fromStdString(dbNameStr) + DB_EXTENSION;
	}
};