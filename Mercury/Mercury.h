#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>
#include <memory>
#include <qdebug.h>
#include "Engine.h"
#include "ui_Mercury.h"
#include "StartNewGameWindow.h"

class Mercury : public QMainWindow
{
	Q_OBJECT

public:
	Mercury(QWidget *parent = Q_NULLPTR);

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
