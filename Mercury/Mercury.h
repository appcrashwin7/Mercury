#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>
#include <qdebug.h>
#include "ui_Mercury.h"
#include "StartNewGameWindow.h"

class Mercury : public QMainWindow
{
	Q_OBJECT

public:
	Mercury(QWidget *parent = Q_NULLPTR);
private slots:
	void showExitAlert();
	void newGameDialog();
	void closeNewGameDialog();
	void loadGameDialog();

private:
	StartNewGameWindow newGameWindow;
	Ui::MercuryClass ui;
};
