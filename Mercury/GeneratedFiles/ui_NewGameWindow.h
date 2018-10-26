/********************************************************************************
** Form generated from reading UI file 'NewGameWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGAMEWINDOW_H
#define UI_NEWGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewGameWindow
{
public:
    QPushButton *startButton;
    QLineEdit *newGameName;
    QLabel *label;

    void setupUi(QWidget *NewGameWindow)
    {
        if (NewGameWindow->objectName().isEmpty())
            NewGameWindow->setObjectName(QStringLiteral("NewGameWindow"));
        NewGameWindow->resize(682, 398);
        startButton = new QPushButton(NewGameWindow);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(530, 340, 121, 41));
        newGameName = new QLineEdit(NewGameWindow);
        newGameName->setObjectName(QStringLiteral("newGameName"));
        newGameName->setGeometry(QRect(120, 20, 113, 20));
        label = new QLabel(NewGameWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 81, 21));

        retranslateUi(NewGameWindow);

        QMetaObject::connectSlotsByName(NewGameWindow);
    } // setupUi

    void retranslateUi(QWidget *NewGameWindow)
    {
        NewGameWindow->setWindowTitle(QApplication::translate("NewGameWindow", "Start new game", Q_NULLPTR));
        startButton->setText(QApplication::translate("NewGameWindow", "Start", Q_NULLPTR));
        label->setText(QApplication::translate("NewGameWindow", "Name of game", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewGameWindow: public Ui_NewGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAMEWINDOW_H
