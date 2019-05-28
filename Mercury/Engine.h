#pragma once

#include <qdatetime>

#include "GameWindow.h"
#include "Universe.h"
#include "Colony.h"
#include "GameSaver.h"

class Engine : public QObject
{
	Q_OBJECT
public:
	Engine(QWidget * mainWindow, QString gameName);
	~Engine();

private:
	QString gameName;
	GameWindow window;
	QDateTime gameTime;
	Universe gameUniverse;
	std::vector<Colony> Colonies;

	void changeTime(TimeChange change = TimeChange::hour_1);
	const CelestialBody * searchBodyByName(const PlanetarySystem & system, const std::string & name);

public slots:
	void showBodyInfo(QTreeWidgetItem * item, int column);
};