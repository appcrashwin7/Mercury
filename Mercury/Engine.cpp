#include "Engine.h"

Engine::Engine(QWidget * mainWindow, QString gameName)
	:gameTime(QDate(2030, 10, 10)), Colonies({ Colony(*(dynamic_cast<RockyBody*>(gameUniverse.getSystem(0).Bodies[3].get())), 
		QuantityT(RESOURCES_LIST_SIZE, 10000), QuantityT({5, 20, 10, 20, 2, 1, 1, 1, 1, 0, 0}))}),
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
	QDateTime prev = gameTime;

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
	}

	auto daysPassed = prev.daysTo(gameTime);
	for (size_t i = 0; i < static_cast<size_t>(daysPassed); i++)
	{
		for (auto & col : Colonies)
		{
			col.simulate();
		}
	}

	QLabel * timeShow = this->window.findChild<QLabel*>("date");
	timeShow->setText(gameTime.toString("d/M/yyyy h:mm AD"));
	window.update();
}

void Engine::showBodyInfo(QTreeWidgetItem * item, int column)
{
	if (item != nullptr)
	{
		QString bodyName = item->text(column);

		QTreeWidget * objectValues = this->window.findChild<QTreeWidget*>("objectValues");
		const CelestialBody * actualBody = searchBodyByName(gameUniverse.getSystem(0), bodyName);

		std::array<QString, 10> bodyProps = {
			QString::number(actualBody->physics.mass.value()) + " kg",
			QString::number(actualBody->physics.radius.value()) + " m",
			QString::number(actualBody->escapeVelocity.value()) + " m/s",
			QString::number(actualBody->surfaceGravity.value()) + " m/s^2",
			QString::number(actualBody->physics.getSurfaceTemperature().value()) + " K",
			(!actualBody->orbit.isDefault) ? gameUniverse.getSystem(0).Bodies[actualBody->orbit.parent.value()].get()->getName() :
			"",
			(!actualBody->orbit.isDefault) ? QString::number(actualBody->orbit.apoapsis.value()) + " m" : "",
			(!actualBody->orbit.isDefault) ? QString::number(actualBody->orbit.periapsis.value()) + " m" : "",
			(!actualBody->orbit.isDefault) ? QString::number(actualBody->orbit.getOrbitalPeriod() / units::days) : "",
			(!actualBody->orbit.isDefault) ? QString::number(actualBody->orbit.eccentricity) : ""
		};

		for (int i = 0; i < objectValues->topLevelItemCount(); i++)
		{
			objectValues->topLevelItem(i)->setText(1, bodyProps[i]);
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

	for (size_t i = 0; i < static_cast<size_t>(TimeChange::month_24) + 1; i++)
	{
		QObject::connect(window.findChild<QPushButton*>("iTime" + QString::number(i + 1)),
			&QPushButton::clicked, [&, i] {changeTime(static_cast<TimeChange>(i)); });
	}

	QComboBox * systemSelect = this->window.findChild<QComboBox*>("systemSelect");
	systemSelect->addItem(this->gameUniverse.getSystem(0).getName(), QVariant(0));
	QTreeWidget * systemObjectTree = this->window.findChild<QTreeWidget*>("systemObjTree");
	QWidget * systemRender = this->window.findChild<QWidget*>(SystemRender::getWidgetName());

	QObject::connect(systemObjectTree, &QTreeWidget::itemClicked, this, &Engine::showBodyInfo);
	QObject::connect(systemObjectTree, &QTreeWidget::itemClicked, dynamic_cast<SystemRender*>(systemRender),
		&SystemRender::changeFirstBody);

	systemObjectTree->setHeaderLabel(this->gameUniverse.getSystem(0).getName());
	for (const auto & body : this->gameUniverse.getSystem(0).Bodies)
	{
		systemObjectTree->addTopLevelItem(new QTreeWidgetItem(QStringList(body.get()->getName())));
	}

	window.putTime(&gameTime);
	window.setSystemToRender(&(gameUniverse.getLastSystem()));
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
