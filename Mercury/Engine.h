#pragma once

#include <qdatetime.h>
#include "GameWindow.h"
#include "Universe.h"

class Engine : public QObject
{
	Q_OBJECT
public:
	Engine(QWidget * mainWindow, QString gameName);
	~Engine();

	int engineLoop();
private:
	GameWindow window;
	QDateTime gameTime;
	Universe gameUniverse;

	void changeTime(TimeChange change = TimeChange::hour_1);
	CelestialBody * searchBodyByName(const PlanetarySystem & system, const std::string & name);

	void generateFirstSystem();

public slots:
	void showBodyInfo(QTreeWidgetItem * item, int column);
};