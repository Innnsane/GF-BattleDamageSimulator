#include "calculation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculation w;
    w.show();

    return a.exec();
}
