#pragma once

#include <qdatetime.h>
#include "GameWindow.h"
#include "Universe.h"

class Engine
{
public:
	Engine(QWidget * mainWindow, QString gameName);
	~Engine();

	int engineLoop();
private:
	GameWindow window;
	QDateTime gameTime;
	Universe gameUniverse;

	void changeTime(TimeChange change = TimeChange::hour_1);
};