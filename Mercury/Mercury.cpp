#include "Mercury.h"

Mercury::Mercury(QWidget *parent)
	: QMainWindow(parent), newGameWindow(nullptr)
{
	ui.setupUi(this);
	QObject::connect(ui.exitButton, &QPushButton::clicked, this, &Mercury::showExitAlert);
	QObject::connect(ui.newGameButton, &QPushButton::clicked, this, &Mercury::newGameDialog);
	QPushButton * nGStartButton = newGameWindow.findChild<QPushButton*>("startButton");
	QObject::connect(nGStartButton, &QPushButton::clicked, this, &Mercury::closeNewGameDialog);
	QObject::connect(ui.loadGameButton, &QPushButton::clicked, this, &Mercury::loadGameDialog);
}

void Mercury::showExitAlert()
{
	QMessageBox box(QMessageBox::Icon::Question, QString("Exit"), QString("Are you sure?"), QMessageBox::Button::Yes | QMessageBox::Button::No);
	box.show();
	if (box.exec() == QMessageBox::Button::Yes)
	{
		this->close();
	}
}

void Mercury::newGameDialog()
{
	this->setVisible(false);
	newGameWindow.show();
}

void Mercury::closeNewGameDialog()
{
	this->setVisible(true);
	newGameWindow.close();
}

void Mercury::loadGameDialog()
{
	QFileDialog saveLoad(this, Qt::Window);
	saveLoad.setNameFilter("Mercury Saves (*.msave)");
	saveLoad.show();
	saveLoad.exec();
}
