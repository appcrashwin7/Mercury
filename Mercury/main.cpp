#include <QtWidgets/QApplication>

#include "Mercury.h"
#include "StartNewGameWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Mercury w;
	w.show();
	
	return a.exec();
}
