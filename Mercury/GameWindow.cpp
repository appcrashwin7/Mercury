#include "GameWindow.h"

GameWindow::GameWindow(QWidget * main = nullptr)
	:QWidget(main)
{
	ui.setupUi(this);
}

GameWindow::~GameWindow()
{}


void GameWindow::closeEvent(QCloseEvent * event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Mercury",
		tr("Are you sure?\n"),
		QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		event->accept();
	}
}