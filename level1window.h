#ifndef LEVEL1WINDOW_H
#define LEVEL1WINDOW_H

#include "gamewindow.h"

class Level1Window : public GameWindow
{
public:
    explicit Level1Window(QWidget* parent = nullptr);
    enum Room {
        ROOM_ONE, ROOM_TWO, ROOM_THREE, ROOM_FOUR
    };

protected:
    using GameWindow::createTiles;
    void createTiles() override;

    void createRoom1();
    void createRoom2();
    void createRoom3();
    void createRoom4();

    void changeRoom(Room newRoom);

private:
    Room m_currentRoom;
};

#endif // LEVEL1WINDOW_H
