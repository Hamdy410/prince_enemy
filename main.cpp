#include "startpage.h"
#include "level1window.h"
#include <QApplication>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage startPage("Prince of Persia", 1);
    Level1Window* LevelWindow = nullptr;

    QObject::connect(&startPage, &StartPage::startRequested, [&]() {
        startPage.close();
        LevelWindow = new Level1Window();
        LevelWindow->show();
    });

    startPage.show();

    return a.exec();
}
