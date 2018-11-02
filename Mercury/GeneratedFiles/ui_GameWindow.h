/********************************************************************************
** Form generated from reading UI file 'GameWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *systemButton;
    QPushButton *colonyButton;
    QPushButton *industryButton;
    QPushButton *scienceButton;
    QPushButton *fleetButton;
    QPushButton *shipButton;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(1079, 813);
        GameWindow->setWindowTitle(QStringLiteral("Mercury"));
        formLayout = new QFormLayout(GameWindow);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(10, 5, 10, 5);
        systemButton = new QPushButton(GameWindow);
        systemButton->setObjectName(QStringLiteral("systemButton"));

        horizontalLayout->addWidget(systemButton);

        colonyButton = new QPushButton(GameWindow);
        colonyButton->setObjectName(QStringLiteral("colonyButton"));

        horizontalLayout->addWidget(colonyButton);

        industryButton = new QPushButton(GameWindow);
        industryButton->setObjectName(QStringLiteral("industryButton"));

        horizontalLayout->addWidget(industryButton);

        scienceButton = new QPushButton(GameWindow);
        scienceButton->setObjectName(QStringLiteral("scienceButton"));

        horizontalLayout->addWidget(scienceButton);

        fleetButton = new QPushButton(GameWindow);
        fleetButton->setObjectName(QStringLiteral("fleetButton"));

        horizontalLayout->addWidget(fleetButton);

        shipButton = new QPushButton(GameWindow);
        shipButton->setObjectName(QStringLiteral("shipButton"));

        horizontalLayout->addWidget(shipButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);


        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        systemButton->setText(QApplication::translate("GameWindow", "System", Q_NULLPTR));
        colonyButton->setText(QApplication::translate("GameWindow", "Colonies", Q_NULLPTR));
        industryButton->setText(QApplication::translate("GameWindow", "Industry", Q_NULLPTR));
        scienceButton->setText(QApplication::translate("GameWindow", "Science", Q_NULLPTR));
        fleetButton->setText(QApplication::translate("GameWindow", "Fleet", Q_NULLPTR));
        shipButton->setText(QApplication::translate("GameWindow", "Ship", Q_NULLPTR));
        Q_UNUSED(GameWindow);
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
