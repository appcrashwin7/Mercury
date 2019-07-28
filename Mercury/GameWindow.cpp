#include "GameWindow.h"

GameWindow::GameWindow(std::vector<Colony> & cls, QWidget * main = nullptr)
	:QWidget(main), colsWindow(cls)
{
	SystemRender * sysR = new SystemRender();

	ui.setupUi(this);
	ui.systemViewCont->addWidget(sysR);
	this->update();

	QPushButton * clsButton = this->findChild<QPushButton*>("colonyButton");

	QObject::connect(clsButton, &QPushButton::clicked, &colsWindow, &ColoniesWindow::show);
	QObject::connect(clsButton, &QPushButton::clicked, &colsWindow, &ColoniesWindow::resetData);
}

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
		this->colsWindow.close();
		event->accept();
	}
}

void GameWindow::putTime(const QDateTime * tm)
{
	auto sysRenderWidget = this->findChildren<QWidget*>(SystemRender::getWidgetName());
	dynamic_cast<SystemRender*>(sysRenderWidget.first())->setTime(tm);
}

void GameWindow::setSystemToRender(const PlanetarySystem * system)
{
	auto sysRenderWidget = this->findChildren<QWidget*>(SystemRender::getWidgetName());
	dynamic_cast<SystemRender*>(sysRenderWidget.first())->setNewSystem(system);
}
