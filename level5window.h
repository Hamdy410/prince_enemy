#ifndef LEVEL5WINDOW_H
#define LEVEL5WINDOW_H

#include "gamewindow.h"

class Level5Window : public GameWindow
{
public:
    explicit Level5Window(QWidget* parent = nullptr, int healthVal=15, int scoreVal=0);
    enum Room {
        ROOM_ONE, ROOM_TWO, ROOM_THREE
    };

protected:
    using GameWindow::createTiles;
    void createTilesandWallsandCeiling() override;
    void createRoom1();
    void createRoom2();
    void createRoom3();
    void getNextRoom() override;
    void getCurrentRoom() override;
    void changeRoom(Room newRoom);

private:
    Room m_currentRoom;
};

#endif // LEVEL5WINDOW_H
