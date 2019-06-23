#include "Mercury.h"

Mercury::Mercury(QWidget *parent)
	: QMainWindow(parent)
{
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
				loader.loadUniverse(), loader.loadColonies(), loader.loadGameTime()));
			game.swap(ptr);
		}
	}
	ui.newGameButton->setEnabled(true);
	ui.loadGameButton->setEnabled(true);
}

void Mercury::playGame()
{
	this->setVisible(false);
	QLineEdit * gameName = newGameWindow.findChild<QLineEdit*>("newGameName");
	std::unique_ptr<Engine> ptr(new Engine(nullptr, gameName->text()));
	game.swap(ptr);
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