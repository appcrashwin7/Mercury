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
	this->gameUniverse.addSystem(PlanetarySystem(Star(0, 695700000, 2.0f * pow(10, 30), 3.75 * pow(10, 28), 0.0122f)));
	this->gameUniverse.getSystem(0).name = "Sol System";
	this->gameUniverse.getSystem(0).mainObject.name = "Sol";

	QComboBox * systemSelect = this->window.findChild<QComboBox*>("systemSelect");
	systemSelect->addItem(QString::fromStdString(this->gameUniverse.getSystem(0).name), QVariant(0));
	QTreeWidget * systemObjectTree = this->window.findChild<QTreeWidget*>("systemObjTree");
	systemObjectTree->setHeaderLabel(QString::fromStdString(this->gameUniverse.getSystem(0).mainObject.name));

	this->showBodyInfo(std::string("Sol"));
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

void Engine::showBodyInfo(const std::string & bodyName)
{
	QTreeWidget * objectValues = this->window.findChild<QTreeWidget*>("objectValues");
	CelestialBody * actualBody = &this->gameUniverse.getSystem(0).mainObject;

	/*
	for (auto t : actualBody->Satellites)
	{
		if (t->name == bodyName)
		{
			QList<QTreeWidgetItem*> Items = objectValues->findItems("*", Qt::MatchFlag::MatchRegExp);

			break;
		}
	}
	*/
	if (actualBody != nullptr)
	{
		if (actualBody->name == bodyName)
		{
			objectValues->findItems(QString("Mass"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(double(actualBody->mass)) + " kg");
			objectValues->findItems(QString("Radius"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(actualBody->radius) + " m");
			objectValues->findItems(QString("Escape velocity"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(actualBody->escapeVelocity) + " m/s");
			objectValues->findItems(QString("Surface gravity"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(actualBody->surfaceGravity) + " m/s^2");
		}
	}
}

void Engine::showBodyInfo(CelestialBody * body)
{
	if (body == nullptr)
	{
		return;
	}

}
