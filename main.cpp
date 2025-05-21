#include "mainwindow.h"
#include "menupage.h"
#include "startpage.h"
#include "tutorialpage.h"
#include "level1window.h"
#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->processEvents(QEventLoop::AllEvents);

    // Create all pages
    MenuPage menuPage("Prince of Persia");
    StartPage* startPage = nullptr;
    TutorialPage* tutorialPage = nullptr;
    Level1Window* levelWindow = nullptr;

    // Connect menu page signals
    QObject::connect(&menuPage, &MenuPage::playGameRequested, [&]() {
        menuPage.hide();
        startPage = new StartPage("Prince of Persia", 1);
        startPage->show();

        // Connect start page signals
        QObject::connect(startPage, &StartPage::startRequested, [&]() {
            startPage->close();
            delete startPage;
            startPage = nullptr;

            levelWindow = new Level1Window();
            levelWindow->show();
        });
    });

    QObject::connect(&menuPage, &MenuPage::tutorialRequested, [&]() {
        menuPage.hide();
        tutorialPage = new TutorialPage();
        tutorialPage->show();

        // Connect tutorial page signals
        QObject::connect(tutorialPage, &TutorialPage::backToMenuRequested, [&]() {
            tutorialPage->close();
            delete tutorialPage;
            tutorialPage = nullptr;

            menuPage.show();
        });
    });

    // Show menu page
    menuPage.show();

    return a.exec();
}
