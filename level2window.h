#ifndef LEVEL2WINDOW_H
#define LEVEL2WINDOW_H

#include "gamewindow.h"

class Level2Window : public GameWindow
{
    Q_OBJECT

public:
    explicit Level2Window(QWidget* parent = nullptr);
    enum Room {
        ROOM_ONE, ROOM_TWO, ROOM_THREE, ROOM_FOUR,ROOM_FIVE,ROOM_SIX,ROOM_SEVEN
    };

signals:
    void Level3Requested();

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
    void getNextRoom() override;
    void getCurrentRoom() override;
    void changeRoom(Room newRoom);

private:
    Room m_currentRoom;
};

#endif // LEVEL1WINDOW_H
