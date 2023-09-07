#include "autorization.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    autorization w;
    w.show();
    return a.exec();
}
