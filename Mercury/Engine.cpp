#include "Engine.h"

Engine::Engine(QWidget * mainWindow, QString gameName)
	:window(mainWindow)
{
	window.show();
}

Engine::~Engine()
{

}

int Engine::engineLoop()
{
	while (false)
	{

	}
	return 0;
}
