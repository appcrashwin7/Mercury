#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Mercury.h"

class Mercury : public QMainWindow
{
	Q_OBJECT

public:
	Mercury(QWidget *parent = Q_NULLPTR);

private:
	Ui::MercuryClass ui;
};
