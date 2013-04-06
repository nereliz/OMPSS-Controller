#include <QCoreApplication>
#include "Controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controller *ctrl = new Controller();
    ctrl->start();
    return a.exec();
}
