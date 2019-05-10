#include "Engine.h"

Engine::Engine(QWidget * mainWindow, QString gameName)
	:gameTime(QDate(2030, 10, 10)), Colonies({ Colony(*(dynamic_cast<Planet*>(gameUniverse.getSystem(0).Bodies[3]))) }),
	window(Colonies, mainWindow)
{
	window.show();
	QLabel * timeShow = this->window.findChild<QLabel*>("date");
	timeShow->setText(gameTime.toString("d/M/yyyy h:mm AD"));

	QPushButton * iTime1h = this->window.findChild<QPushButton*>("iTime1h");
	QPushButton * iTime6h = this->window.findChild<QPushButton*>("iTime6h");


	QObject::connect(iTime1h, &QPushButton::clicked, [=] {this->changeTime(TimeChange::hour_1); });
	QObject::connect(iTime6h, &QPushButton::clicked, [=] {this->changeTime(TimeChange::hour_6); });

	
	QComboBox * systemSelect = this->window.findChild<QComboBox*>("systemSelect");
	systemSelect->addItem(QString::fromStdString(this->gameUniverse.getSystem(0).name), QVariant(0));
	QTreeWidget * systemObjectTree = this->window.findChild<QTreeWidget*>("systemObjTree");

	QObject::connect(systemObjectTree, &QTreeWidget::itemClicked, this, &Engine::showBodyInfo);

	systemObjectTree->setHeaderLabel(QString::fromStdString(this->gameUniverse.getSystem(0).name));
	for (const auto body : this->gameUniverse.getSystem(0).Bodies)
	{
		systemObjectTree->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(body->name))));
	}
}

void Engine::changeTime(TimeChange change)
{
	const qint64 hour = 3600;

	switch (change)
	{
	case TimeChange::hour_1:
		this->gameTime = this->gameTime.addSecs(hour);
		break;
	case TimeChange::hour_6:
		this->gameTime = this->gameTime.addSecs(hour * 6);
		break;
	case TimeChange::hour_12:
		this->gameTime = this->gameTime.addSecs(hour * 12);
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
		CelestialBody * actualBody = searchBodyByName(gameUniverse.getSystem(0), bodyName.toStdString());

		auto setItemValue = [objectValues](QString item, QString value)->void
		{
			objectValues->findItems(item, Qt::MatchFlag::MatchExactly)[0]->setText(1, value);
		};

		if (actualBody != nullptr)
		{
			setItemValue("Mass", QString::number(actualBody->mass) + " kg");
			setItemValue("Radius", QString::number(actualBody->radius) + " m");
			setItemValue("Escape velocity", QString::number(actualBody->escapeVelocity) + " m/s");
			setItemValue("Surface gravity", QString::number(actualBody->surfaceGravity) + " m/s^2");

			if (!actualBody->bodyOrbit.isZero)
			{
				setItemValue("Apoapsis", QString::number(actualBody->bodyOrbit.apoapsis) + " m");
				setItemValue("Periapsis", QString::number(actualBody->bodyOrbit.periapsis) + " m");
			}
			else
			{
				setItemValue("Apoapsis", "---");
				setItemValue("Periapsis", "---");
			}

			if (actualBody->parent != nullptr)
				setItemValue("Parent body", QString::fromStdString(actualBody->parent->name));
			else
				setItemValue("Parent body", "---");
		}
	}
}

CelestialBody * Engine::searchBodyByName(const PlanetarySystem & system, const std::string & name)
{
	if (!system.Bodies.empty())
	{
		for (auto t : system.Bodies)
		{
			if (t->name == name)
			{
				return t;
			}
		}
	}
	return nullptr;
}