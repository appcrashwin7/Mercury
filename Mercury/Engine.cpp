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

	generateFirstSystem();

	QComboBox * systemSelect = this->window.findChild<QComboBox*>("systemSelect");
	systemSelect->addItem(QString::fromStdString(this->gameUniverse.getSystem(0).name), QVariant(0));
	QTreeWidget * systemObjectTree = this->window.findChild<QTreeWidget*>("systemObjTree");

	QObject::connect(systemObjectTree, &QTreeWidget::itemClicked, this, &Engine::showBodyInfo);

	systemObjectTree->setHeaderLabel(QString::fromStdString(this->gameUniverse.getSystem(0).mainObject.name));
	for (auto mainSatellites : this->gameUniverse.getSystem(0).mainObject.getSatellites())
	{
		systemObjectTree->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(mainSatellites->name))));
	}
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

void Engine::showBodyInfo(QTreeWidgetItem * item, int column)
{
	if (item != nullptr)
	{
		QString bodyName = item->text(column);

		QTreeWidget * objectValues = this->window.findChild<QTreeWidget*>("objectValues");
		CelestialBody * actualBody = searchBodyByName(&gameUniverse.getSystem(0).mainObject, bodyName.toStdString());

		if (actualBody != nullptr)
		{
				objectValues->findItems(QString("Mass"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(double(actualBody->mass)) + " kg");
				objectValues->findItems(QString("Radius"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(actualBody->radius) + " m");
				objectValues->findItems(QString("Escape velocity"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(actualBody->escapeVelocity) + " m/s");
				objectValues->findItems(QString("Surface gravity"), Qt::MatchFlag::MatchExactly).operator[](0)->setText(1, QString::number(actualBody->surfaceGravity) + " m/s^2");
		}
	}
}

CelestialBody * Engine::searchBodyByName(CelestialBody * body, const std::string & name)
{
	if (body != nullptr)
	{
		if (body->name == name)
		{
			return body;
		}
		else
		{
			for (auto i : body->getSatellites())
			{
				auto a = searchBodyByName(i, name);
				if (a != nullptr)
				{
					return a;
				}
			}
			return nullptr;
		}
	}
	return nullptr;
}

void Engine::generateFirstSystem()
{
	this->gameUniverse.addSystem(PlanetarySystem(Star(6.9 * pow(10, 8), 2.0 * pow(10, 30), 3.75 * pow(10, 28), 0.0122f, "Sol")));
	this->gameUniverse.getSystem(0).name = "Sol System";

	this->gameUniverse.getSystem(0).mainObject.getSatellites().push_back(new Planet(
		CelestialBody(2.4 * pow(10, 6), 3.3 * pow(10, 23), CelestialBodyType::Planet, &(this->gameUniverse.getSystem(0).mainObject), Orbit(6.9 * pow(10, 10), 4.9 * pow(10, 10)), "Mercury")));
	this->gameUniverse.getSystem(0).mainObject.getSatellites().push_back(new Planet(
		CelestialBody(6.0 * pow(10, 6), 4.8 * pow(10, 24), CelestialBodyType::Planet, &(this->gameUniverse.getSystem(0).mainObject), Orbit(1.08 * pow(10, 11), 1.07 * pow(10, 11)), "Venus")));
	this->gameUniverse.getSystem(0).mainObject.getSatellites().push_back(new Planet(
		CelestialBody(6.3 * pow(10, 6), 5.9 * pow(10, 24), CelestialBodyType::Planet, &(this->gameUniverse.getSystem(0).mainObject), Orbit(1.52 * pow(10, 11), 1.47 * pow(10, 11)), "Earth")));
	this->gameUniverse.getSystem(0).mainObject.getSatellites().back()->getSatellites().push_back(new Planet(CelestialBody(1.7 * pow(10, 6), 7.3 * pow(10, 22), CelestialBodyType::Planet,
		this->gameUniverse.getSystem(0).mainObject.getSatellites().back(), Orbit(4 * pow(10, 8), 3.6 * pow(10, 8)), "Luna")));
}
