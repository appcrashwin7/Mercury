#pragma once 

#include <QtWidgets/qwidget.h>

#include "Colony.h"
#include "Universe.h"

#include "ui_SystemView.h"

class SystemView : public QWidget
{
    Q_OBJECT

    Ui_SystemView ui;
    std::vector<Colony>* cls;
    Universe* universe;
public:
    SystemView() = delete;
    SystemView(std::vector<Colony>* cl, Universe* u);
    ~SystemView() = default;

private:
    void fillSystemTable();
};