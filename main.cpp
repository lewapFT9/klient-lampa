#include "lampa.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lampa w;
    w.show();
    return a.exec();
}
