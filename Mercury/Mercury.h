#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>
#include <memory>
#include <qdebug.h>

#include "Engine.h"
#include "GameLoader.h"
#include "ui_Mercury.h"
#include "StartNewGameWindow.h"
#include "Architecture.h"

class Mercury : public QMainWindow
{
	Q_OBJECT

public:
	Mercury(QWidget * parent = nullptr);

	void closeEvent(QCloseEvent * event);
private slots:
	void newGameDialog();
	void closeNewGameDialog();
	void loadGameDialog();
	void playGame();

private:
	StartNewGameWindow newGameWindow;
	Ui::MercuryClass ui;
	std::unique_ptr<Engine> game;
};
