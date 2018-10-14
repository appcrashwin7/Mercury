/********************************************************************************
** Form generated from reading UI file 'MercuryGame.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MERCURYGAME_H
#define UI_MERCURYGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MercuryGame
{
public:

    void setupUi(QWidget *MercuryGame)
    {
        if (MercuryGame->objectName().isEmpty())
            MercuryGame->setObjectName(QStringLiteral("MercuryGame"));
        MercuryGame->resize(507, 403);

        retranslateUi(MercuryGame);

        QMetaObject::connectSlotsByName(MercuryGame);
    } // setupUi

    void retranslateUi(QWidget *MercuryGame)
    {
        MercuryGame->setWindowTitle(QApplication::translate("MercuryGame", "MercuryGame", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MercuryGame: public Ui_MercuryGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MERCURYGAME_H
