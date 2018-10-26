/********************************************************************************
** Form generated from reading UI file 'Mercury.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MERCURY_H
#define UI_MERCURY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MercuryClass
{
public:
    QWidget *centralWidget;
    QPushButton *newGameButton;
    QPushButton *loadGameButton;
    QPushButton *exitButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MercuryClass)
    {
        if (MercuryClass->objectName().isEmpty())
            MercuryClass->setObjectName(QStringLiteral("MercuryClass"));
        MercuryClass->resize(600, 400);
        centralWidget = new QWidget(MercuryClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        newGameButton = new QPushButton(centralWidget);
        newGameButton->setObjectName(QStringLiteral("newGameButton"));
        newGameButton->setGeometry(QRect(210, 60, 161, 51));
        loadGameButton = new QPushButton(centralWidget);
        loadGameButton->setObjectName(QStringLiteral("loadGameButton"));
        loadGameButton->setGeometry(QRect(210, 140, 161, 51));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(210, 220, 161, 51));
        MercuryClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MercuryClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MercuryClass->setStatusBar(statusBar);

        retranslateUi(MercuryClass);

        QMetaObject::connectSlotsByName(MercuryClass);
    } // setupUi

    void retranslateUi(QMainWindow *MercuryClass)
    {
        MercuryClass->setWindowTitle(QApplication::translate("MercuryClass", "Mercury", Q_NULLPTR));
        newGameButton->setText(QApplication::translate("MercuryClass", "Start New Game", Q_NULLPTR));
        loadGameButton->setText(QApplication::translate("MercuryClass", "Load Game", Q_NULLPTR));
        exitButton->setText(QApplication::translate("MercuryClass", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MercuryClass: public Ui_MercuryClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MERCURY_H
