#include "Engine.h"

Engine::Engine(QWidget * mainWindow, QString gameName)
	:gameTime(QDate(2030, 10, 10)), window(gameUniverse, mainWindow), gameName(gameName)
{
	init();
}

Engine::Engine(QWidget * mainWindow, QString gameName, Universe universe, QDateTime time)
	:gameTime(std::move(time)), gameUniverse(std::move(universe)),
	gameName(std::move(gameName)), window(gameUniverse, mainWindow)
{
	init();
}

Engine::~Engine()
{
	auto save = gameName + GAME_SAVE_EXTENSION;
	GameSaver saver(save);
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
	gameUniverse.simulate(prev.daysTo(gameTime));

	QLabel * timeShow = this->window.findChild<QLabel*>("date");
	timeShow->setText(gameTime.toString(GAME_TIME_FORMAT));
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
			MassToText(actualBody->physics.mass, false, false, true),
			LengthToText(actualBody->physics.radius, true, false, false),
			VelocityToText(actualBody->escapeVelocity, false, false),
			AccelerationToText(actualBody->surfaceGravity, false, false),
			TemperatureToText(actualBody->physics.getSurfaceTemperature()),
			(actualBody->orbit.parent) ? gameUniverse.getSystem(0).
			Bodies[actualBody->orbit.parent.value()].get()->getName() : "",
			(actualBody->orbit.parent) ? LengthToText(actualBody->orbit.apoapsis, false, false, true) : "",
			(actualBody->orbit.parent) ? TimeToText(actualBody->orbit.getOrbitalPeriod(), 2) : "",
			(actualBody->orbit.parent) ? LengthToText(actualBody->orbit.periapsis, false, false, true) : "",
			(actualBody->orbit.parent) ? QString::number(actualBody->orbit.eccentricity) : ""
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
