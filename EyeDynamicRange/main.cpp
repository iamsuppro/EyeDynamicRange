#include "EyeDynamicRange.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EyeDynamicRange w;
    w.show();
    return a.exec();
}
