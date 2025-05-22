#include <QApplication>
#include "gamemanager.h"
#include "level1window.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.processEvents(QEventLoop::AllEvents);
    GameManager gameManager;
    gameManager.start();

    return a.exec();
}
