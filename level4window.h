#ifndef LEVEL4WINDOW_H
#define LEVEL4WINDOW_H

#include "gamewindow.h"

class Level4Window : public GameWindow
{
public:
    explicit Level4Window(QWidget* parent = nullptr);
    enum Room {
        ROOM_ONE, ROOM_TWO, ROOM_THREE, ROOM_FOUR
    };

protected:
    using GameWindow::createTiles;
    void createTilesandWallsandCeiling() override;
    void createRoom1();
    void createRoom2();
    void createRoom3();
    void createRoom4();
    void getNextRoom() override;
    void getCurrentRoom() override;
    void changeRoom(Room newRoom);

private:
    Room m_currentRoom;
};

#endif // LEVEL3WINDOW_H
