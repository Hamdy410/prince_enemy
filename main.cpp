#include "mainwindow.h"
#include "level1window.h"
#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Level1Window w;
    w.show();
    return a.exec();
}
