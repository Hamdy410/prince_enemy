#include "mainwindow.h"
#include "startpage.h"
#include "level1window.h"
#include "gamewindow.h"
#include <QApplication>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->processEvents(QEventLoop::AllEvents);
    StartPage startPage("Prince of Persia", 1);
    Level1Window* LevelWindow = nullptr;

    QObject::connect(&startPage, &StartPage::startRequested, [&]() {
        startPage.close();
        LevelWindow = new Level1Window();
        LevelWindow->show();
    });

    Level1Window w;
    w.show();
    startPage.show();

    return a.exec();
}
