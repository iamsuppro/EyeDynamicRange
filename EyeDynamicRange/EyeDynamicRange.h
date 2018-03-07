#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EyeDynamicRange.h"

class EyeDynamicRange : public QMainWindow
{
    Q_OBJECT

public:
    EyeDynamicRange(QWidget *parent = Q_NULLPTR);

private:
    Ui::EyeDynamicRangeClass ui;
};
