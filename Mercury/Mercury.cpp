#include "Mercury.h"

Mercury::Mercury(QWidget *parent)
	: QMainWindow(parent)
{
    Commodities::load();
    Architecture::load();

	ui.setupUi(this);
	QObject::connect(ui.exitButton, &QPushButton::clicked, this, &Mercury::close);
	QObject::connect(ui.newGameButton, &QPushButton::clicked, this, &Mercury::newGameDialog);
	QPushButton * nGStartButton = newGameWindow.findChild<QPushButton*>("startButton");
	QObject::connect(nGStartButton, &QPushButton::clicked, this, &Mercury::closeNewGameDialog);
	QObject::connect(ui.loadGameButton, &QPushButton::clicked, this, &Mercury::loadGameDialog);
	QObject::connect(ui.aboutButton, &QPushButton::clicked, []() {
		QMessageBox a("About Mercury",
			"Mercury ver.0.0.0001 <br> Copyright (C) 2019  appcrashwin7 <br><br>" \
			"This program comes with ABSOLUTELY NO WARRANTY<br>" \
			"This is free software, and you are welcome to redistribute it under certain conditions<br>",
			QMessageBox::Icon::Information,
			QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
		a.exec();
	});
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
	playGame();
}

void Mercury::loadGameDialog()
{
	ui.newGameButton->setEnabled(false);
	ui.loadGameButton->setEnabled(false);

	QFileDialog saveLoad(this, tr("Open Save"), QDir::currentPath(), "Mercury Saves (*.msave)");
	saveLoad.show();
	if (saveLoad.exec())
	{
		auto file = saveLoad.selectedFiles()[0];
		if (!file.isEmpty())
		{
			this->setVisible(false);
			auto fileStr = file.toStdString();
			auto fileNameBeg = fileStr.find_last_of('/') + 1;
			fileStr = fileStr.substr(fileNameBeg, fileStr.find_last_of('.') - fileNameBeg);

			GameLoader loader(file);

			std::unique_ptr<Engine> ptr(new Engine(nullptr, QString::fromStdString(fileStr), 
				loader.loadUniverse(), loader.loadGameTime()));
			game.swap(ptr);
		}
	}
	ui.newGameButton->setEnabled(true);
	ui.loadGameButton->setEnabled(true);
}

void Mercury::playGame()
{
	this->setVisible(false);

    JsonDataFile dtFile;
    if (dtFile.load(Mercury::GameStartConfigFile))
    {
        Universe universe;
        auto doc = dtFile.get();

        if (doc.isObject())
        {
            universe.addSystem(doc["system"]["name"].toString());
            const auto& bodies = doc["system"]["bodies"].toArray();
            CelestialBodyFactory bfact;

            for (int i = 0; i < bodies.size(); i++)
            {
                const auto& body = bodies[i];

                PhysicalProperties physProps(
                    body["radius"].toDouble() * units::si::meters,
                    body["mass"].toDouble() * units::si::kilogram, 
                    body["temperature"].toInt() * units::si::kelvins);
                auto name = body["name"].toString();

                if (!(body["orbit"].isUndefined()))
                {
                    const auto& bodyOrbit = body["orbit"];
                    auto parentID = std::make_optional(bodyOrbit["parent"].toInt());
                    auto parentBodyMass = universe.getLastSystem().Bodies[parentID.value()]->physics.mass;

                    Orbit orb = (!bodyOrbit["radius"].isUndefined()) ?
                        Orbit(bodyOrbit["radius"].toDouble() * units::si::meters,
                            parentBodyMass, parentID) :
                        Orbit(bodyOrbit["apo"].toDouble() * units::si::meters,
                            bodyOrbit["per"].toDouble() * units::si::meters,
                            parentBodyMass, parentID);

                    universe.getLastSystem().Bodies.emplace_back(bfact.createBody(physProps, orb, name));
                }
                else
                {
                    universe.getLastSystem().Bodies.emplace_back(bfact.createBody(physProps, Orbit(), name));
                }
            }

            QDate time(doc["time"]["y"].toInt(), doc["time"]["m"].toInt(), doc["time"]["d"].toInt());


            std::vector<ColonyData> colDt;
            const auto& cols = doc["colonies"].toArray();
            for (int i = 0; i < cols.size(); i++)
            {
                const auto& colony = cols[i];
                auto number = colony["number"].toInt();

                QuantityT stock(Commodities::get().size(), colony["stock"].toInt());
                QuantityT buildings(Architecture::get().size(), 0);

                auto findIDofBuilding = [&](const std::string& bName)->int64_t
                {
                    for (size_t ret = 0; ret < Architecture::get().size(); ret++)
                    {
                        if (bName == Architecture::get()[ret].getName())
                        {
                            return ret;
                        }
                    }
                    return -1;
                };

                const auto& buildDt = colony["buildings"].toArray();
                for (int b = 0; b < buildDt.size(); b++)
                {
                    auto pair = JsonDataFile::extractPairValues(buildDt[b], "i");

                    auto id = findIDofBuilding(pair.first);
                    if (id != -1)
                    {
                        buildings[id] = std::stoi(pair.second);
                    }
                }

                colDt.emplace_back(std::make_tuple(
                    std::make_pair(universe.getSystems().size() - 1, number),
                    stock, buildings));
            }

            universe.constructPlayerFactionCols(colDt);
            QLineEdit* gameName = newGameWindow.findChild<QLineEdit*>("newGameName");

            if (gameName->text().size() > 0)
            {
                std::unique_ptr<Engine> ptr(new Engine(nullptr, gameName->text(), std::move(universe), QDateTime(time)));
                game.swap(ptr);
            }
        }
    }
}

void Mercury::closeEvent(QCloseEvent * event)
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