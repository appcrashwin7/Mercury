#include "Engine.h"

Engine::Engine(QWidget * mainWindow, QString gameName)
	:window(mainWindow), gameTime(QDate(2030,10,10))
{
	window.show();
	QLabel * timeShow = this->window.findChild<QLabel*>("date");
	timeShow->setText(gameTime.toString("d/M/yyyy h:mm AD"));

	QPushButton * iTime1h = this->window.findChild<QPushButton*>("iTime1h");
	QPushButton * iTime6h = this->window.findChild<QPushButton*>("iTime6h");
	QObject::connect(iTime1h, &QPushButton::clicked, [=] {this->changeTime(TimeChange::hour_1); });
	QObject::connect(iTime6h, &QPushButton::clicked, [=] {this->changeTime(TimeChange::hour_6); });


	//QObject::connect(this->gameTime, &QDateTime::ad)
	//generate first system
	this->gameUniverse.addSystem(PlanetarySystem(Star(0, 695700, 1.9885f * pow(10, 27), 3.75 * pow(10, 28), 0.0122f)));
	this->gameUniverse.getSystem(0).name = "Sol System";
	QComboBox * systemView = this->window.findChild<QComboBox*>("systemView");
	systemView->addItem(QString::fromStdString(this->gameUniverse.getSystem(0).name), QVariant(0));

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

void Engine::changeTime(TimeChange change)
{
	switch (change)
	{
	case TimeChange::hour_1:
		this->gameTime = this->gameTime.addSecs(3600);
		break;
	case TimeChange::hour_6:
		this->gameTime = this->gameTime.addSecs(3600 * 6);
		break;
	case TimeChange::hour_12:
		this->gameTime = this->gameTime.addSecs(3600 * 12);
		break;
	case TimeChange::hour_24:
		this->gameTime = this->gameTime.addDays(1);
		break;
	case TimeChange::day_7:
		this->gameTime = this->gameTime.addDays(7);
		break;
	case TimeChange::day_30:
		this->gameTime = this->gameTime.addDays(30);
		break;
	case TimeChange::month_6:
		this->gameTime = this->gameTime.addMonths(6);
		break;
	case TimeChange::month_12:
		this->gameTime = this->gameTime.addMonths(12);
		break;
	case TimeChange::month_24:
		this->gameTime = this->gameTime.addMonths(24);
		break;
	default:
		break;
	}
	QLabel * timeShow = this->window.findChild<QLabel*>("date");
	timeShow->setText(gameTime.toString("d/M/yyyy h:mm AD"));
}