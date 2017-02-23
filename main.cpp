#include "cfgmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cfgmanager w;
    w.show();

    return a.exec();
}
