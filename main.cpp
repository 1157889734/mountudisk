#include <QCoreApplication>
#include "head.h"
#include "checkudisk.h"
#include "widget.h"
#include <QApplication>

class checkUdisk;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    checkUdisk check;
    check.started();
    return a.exec();
}
