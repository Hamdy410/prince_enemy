#ifndef LEVEL5WINDOW_H
#define LEVEL5WINDOW_H

#include "gamewindow.h"

class Level5Window : public GameWindow
{
public:
    explicit Level5Window(QWidget* parent = nullptr);
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

#endif // LEVEL5WINDOW_H
