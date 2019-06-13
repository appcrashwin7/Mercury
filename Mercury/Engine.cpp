#include "Engine.h"

Engine::Engine(QWidget * mainWindow, QString gameName)
	:gameTime(QDate(2030, 10, 10)), Colonies({ Colony(*(dynamic_cast<RockyBody*>(gameUniverse.getSystem(0).Bodies[3].get()))) }),
	window(Colonies, mainWindow), gameName(gameName)
{
	init();
}

Engine::Engine(QWidget * mainWindow, QString gameName, Universe universe, std::vector<ColonyData> dt, QDateTime time)
	:gameTime(std::move(time)), gameUniverse(std::move(universe)),
	Colonies(std::move(constructColonies(std::move(dt)))), gameName(std::move(gameName)),
	window(Colonies, mainWindow)
{
	init();
}

Engine::~Engine()
{
	auto save = gameName + GAME_SAVE_EXTENSION;
	GameSaver saver(save);
	saver.addColonies(&Colonies);
	saver.addUniverse(&gameUniverse);
	saver.addGameTime(&gameTime);
	saver();
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
		const CelestialBody * actualBody = searchBodyByName(gameUniverse.getSystem(0), bodyName);

		auto setItemValue = [objectValues](const QString & item, QString value = "---")->void
		{
			objectValues->findItems(item, Qt::MatchFlag::MatchExactly)[0]->setText(1, value);
		};

		if (actualBody != nullptr)
		{
			setItemValue("Mass", QString::number(actualBody->physics.mass.value()) + " kg");
			setItemValue("Radius", QString::number(actualBody->physics.radius.value()) + " m");
			setItemValue("Escape velocity", QString::number(actualBody->escapeVelocity.value()) + " m/s");
			setItemValue("Surface gravity", QString::number(actualBody->surfaceGravity.value()) + " m/s^2");
			setItemValue("Surface temperature", QString::number(actualBody->physics.getSurfaceTemperature().value()) + " K");

			if (!actualBody->orbit.isDefault)
			{
				setItemValue("Apoapsis", QString::number(actualBody->orbit.apoapsis.value()) + " m");
				setItemValue("Periapsis", QString::number(actualBody->orbit.periapsis.value()) + " m");
				setItemValue("Eccentricity", QString::number(actualBody->orbit.eccentricity));
				setItemValue("Orbital period", QString::number(actualBody->orbit.getOrbitalPeriod() / units::days));
				setItemValue("Parent body", gameUniverse.getSystem(0).Bodies[actualBody->orbit.parent.value()].get()->getName());
			}
			else
			{
				setItemValue("Apoapsis");
				setItemValue("Periapsis");
				setItemValue("Eccentricity");
				setItemValue("Orbital period");
				setItemValue("Parent body");
			}
		}
	}
}

const CelestialBody * Engine::searchBodyByName(const PlanetarySystem & system, const QString & name)
{
	auto result = std::find_if(system.Bodies.begin(), system.Bodies.end(), [name](const CelestialBodyPtr & body)->bool 
	{
		if (body.get()->getName() == name)
		{
			return true;
		}
		return false;
	});
	return result.operator*().get();
}

void Engine::init()
{
	window.setWindowTitle(QString("Mercury ") + gameName);
	window.show();
	QLabel * timeShow = this->window.findChild<QLabel*>("date");
	timeShow->setText(gameTime.toString(GAME_TIME_FORMAT));

	QPushButton * iTime1h = this->window.findChild<QPushButton*>("iTime1h");
	QPushButton * iTime6h = this->window.findChild<QPushButton*>("iTime6h");


	QObject::connect(iTime1h, &QPushButton::clicked, [=] {this->changeTime(TimeChange::hour_1); });
	QObject::connect(iTime6h, &QPushButton::clicked, [=] {this->changeTime(TimeChange::hour_6); });


	QComboBox * systemSelect = this->window.findChild<QComboBox*>("systemSelect");
	systemSelect->addItem(this->gameUniverse.getSystem(0).getName(), QVariant(0));
	QTreeWidget * systemObjectTree = this->window.findChild<QTreeWidget*>("systemObjTree");

	QObject::connect(systemObjectTree, &QTreeWidget::itemClicked, this, &Engine::showBodyInfo);

	systemObjectTree->setHeaderLabel(this->gameUniverse.getSystem(0).getName());
	for (const auto & body : this->gameUniverse.getSystem(0).Bodies)
	{
		systemObjectTree->addTopLevelItem(new QTreeWidgetItem(QStringList(body.get()->getName())));
	}
}

std::vector<Colony> Engine::constructColonies(std::vector<ColonyData> data)
{
	std::vector<Colony> ret;

	for (const auto & i : data)
	{
		auto id = std::get<0>(i);
		ret.emplace_back(Colony(*(dynamic_cast<RockyBody*>(gameUniverse.getSystem(id.first).Bodies[id.second].get())),
			std::get<1>(i), std::get<2>(i)));
	}

	return ret;
}
