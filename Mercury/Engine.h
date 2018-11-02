#pragma once

#include "GameWindow.h"

class Engine
{
public:
	Engine(QWidget * mainWindow, QString gameName);
	~Engine();

	int engineLoop();

private:
	GameWindow window;
};