#ifndef LEVEL1WINDOW_H
#define LEVEL1WINDOW_H

#include "gamewindow.h"

class Level1Window : public GameWindow
{
    Q_OBJECT

public:
    explicit Level1Window(QWidget* parent = nullptr, int healthVal=15, int scoreVal=0);
    enum Room {
        ROOM_ONE, ROOM_TWO, ROOM_THREE, ROOM_FOUR,ROOM_FIVE,ROOM_SIX,ROOM_SEVEN,ROOM_EIGHT
    };

signals:
    void Level2Requested();

protected:
    using GameWindow::createTiles;
    void createTilesandWallsandCeiling() override;
    void createRoom1();
    void createRoom2();
    void createRoom3();
    void createRoom4();
    void createRoom5();
    void createRoom6();
    void createRoom7();
    void createRoom8();
    void getNextRoom() override;
    void getCurrentRoom() override;
    void changeRoom(Room newRoom);

private:
    Room m_currentRoom;
};

#endif // LEVEL1WINDOW_H
