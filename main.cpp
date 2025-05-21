#include "mainwindow.h"
#include "menupage.h"
#include "startpage.h"
#include "tutorialpage.h"
#include "level1window.h"
#include "level2window.h"
#include "gamewindow.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->processEvents(QEventLoop::AllEvents);

    // Create all pages
    MenuPage* menuPage = new MenuPage("Prince of Persia");

    // Connect menu page signals - use capture by value for pointers
    QObject::connect(menuPage, &MenuPage::playGameRequested, [=]() {
        menuPage->hide();
        StartPage* startPage = new StartPage("Prince of Persia", 1);

        // Connect start page signals
        QObject::connect(startPage, &StartPage::startRequested, [=]() {
            startPage->close();
            delete startPage;

            Level1Window* levelWindow = new Level1Window();

            // Connect the Level2Requested signal
            QObject::connect(levelWindow, &Level1Window::Level2Requested, [=]() {
                levelWindow->disconnect();
                levelWindow->close();
                delete levelWindow;

                // Add a delay before showing the StartPage for Level 2
                QTimer::singleShot(500, [=]() {
                    // Create StartPage for Level 2
                    StartPage* level2StartPage = new StartPage("Prince of Persia", 2);

                    // Connect Level 2 start page signals
                    QObject::connect(level2StartPage, &StartPage::startRequested, [=]() {
                        level2StartPage->close();
                        delete level2StartPage;

                        Level2Window* level2Window = new Level2Window();
                        level2Window->show();
                    });

                    level2StartPage->show();
                });
            });

            levelWindow->show();
        });

        startPage->show();
    });

    QObject::connect(menuPage, &MenuPage::tutorialRequested, [=]() {
        menuPage->hide();
        TutorialPage* tutorialPage = new TutorialPage();

        // Connect tutorial page signals
        QObject::connect(tutorialPage, &TutorialPage::backToMenuRequested, [=]() {
            tutorialPage->close();
            delete tutorialPage;
            menuPage->show();
        });

        tutorialPage->show();
    });

    // Show menu page
    menuPage->show();
    return a.exec();
}
