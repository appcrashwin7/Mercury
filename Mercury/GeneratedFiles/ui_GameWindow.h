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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *colonyButton;
    QPushButton *systemButton;
    QPushButton *industryButton;
    QPushButton *scienceButton;
    QPushButton *fleetButton;
    QPushButton *shipButton;
    QLabel *date;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *iTime1h;
    QPushButton *iTime6h;
    QPushButton *iTime12h;
    QPushButton *iTime24h;
    QPushButton *iTime7d;
    QPushButton *iTime30d;
    QPushButton *iTime6m;
    QPushButton *iTime12m;
    QPushButton *iTime24m;
    QComboBox *systemView;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(1009, 813);
        GameWindow->setWindowTitle(QStringLiteral("Mercury"));
        formLayout = new QFormLayout(GameWindow);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(10, 5, 10, 5);
        colonyButton = new QPushButton(GameWindow);
        colonyButton->setObjectName(QStringLiteral("colonyButton"));

        horizontalLayout->addWidget(colonyButton);

        systemButton = new QPushButton(GameWindow);
        systemButton->setObjectName(QStringLiteral("systemButton"));

        horizontalLayout->addWidget(systemButton);

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


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        date = new QLabel(GameWindow);
        date->setObjectName(QStringLiteral("date"));

        formLayout->setWidget(2, QFormLayout::LabelRole, date);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        iTime1h = new QPushButton(GameWindow);
        iTime1h->setObjectName(QStringLiteral("iTime1h"));

        horizontalLayout_2->addWidget(iTime1h);

        iTime6h = new QPushButton(GameWindow);
        iTime6h->setObjectName(QStringLiteral("iTime6h"));

        horizontalLayout_2->addWidget(iTime6h);

        iTime12h = new QPushButton(GameWindow);
        iTime12h->setObjectName(QStringLiteral("iTime12h"));

        horizontalLayout_2->addWidget(iTime12h);

        iTime24h = new QPushButton(GameWindow);
        iTime24h->setObjectName(QStringLiteral("iTime24h"));

        horizontalLayout_2->addWidget(iTime24h);

        iTime7d = new QPushButton(GameWindow);
        iTime7d->setObjectName(QStringLiteral("iTime7d"));

        horizontalLayout_2->addWidget(iTime7d);

        iTime30d = new QPushButton(GameWindow);
        iTime30d->setObjectName(QStringLiteral("iTime30d"));

        horizontalLayout_2->addWidget(iTime30d);

        iTime6m = new QPushButton(GameWindow);
        iTime6m->setObjectName(QStringLiteral("iTime6m"));

        horizontalLayout_2->addWidget(iTime6m);

        iTime12m = new QPushButton(GameWindow);
        iTime12m->setObjectName(QStringLiteral("iTime12m"));

        horizontalLayout_2->addWidget(iTime12m);

        iTime24m = new QPushButton(GameWindow);
        iTime24m->setObjectName(QStringLiteral("iTime24m"));

        horizontalLayout_2->addWidget(iTime24m);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        systemView = new QComboBox(GameWindow);
        systemView->setObjectName(QStringLiteral("systemView"));

        formLayout->setWidget(3, QFormLayout::LabelRole, systemView);


        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        colonyButton->setText(QApplication::translate("GameWindow", "Colonies", Q_NULLPTR));
        systemButton->setText(QApplication::translate("GameWindow", "System", Q_NULLPTR));
        industryButton->setText(QApplication::translate("GameWindow", "Industry", Q_NULLPTR));
        scienceButton->setText(QApplication::translate("GameWindow", "Science", Q_NULLPTR));
        fleetButton->setText(QApplication::translate("GameWindow", "Fleet", Q_NULLPTR));
        shipButton->setText(QApplication::translate("GameWindow", "Ship", Q_NULLPTR));
        date->setText(QString());
        iTime1h->setText(QApplication::translate("GameWindow", "+1h", Q_NULLPTR));
        iTime6h->setText(QApplication::translate("GameWindow", "+6h", Q_NULLPTR));
        iTime12h->setText(QApplication::translate("GameWindow", "+12h", Q_NULLPTR));
        iTime24h->setText(QApplication::translate("GameWindow", "+24h", Q_NULLPTR));
        iTime7d->setText(QApplication::translate("GameWindow", "+7d", Q_NULLPTR));
        iTime30d->setText(QApplication::translate("GameWindow", "+30d", Q_NULLPTR));
        iTime6m->setText(QApplication::translate("GameWindow", "+6m", Q_NULLPTR));
        iTime12m->setText(QApplication::translate("GameWindow", "+12m", Q_NULLPTR));
        iTime24m->setText(QApplication::translate("GameWindow", "+24m", Q_NULLPTR));
        Q_UNUSED(GameWindow);
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
