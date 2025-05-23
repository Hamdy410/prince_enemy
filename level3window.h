#ifndef LEVEL3WINDOW_H
#define LEVEL3WINDOW_H

#include "gamewindow.h"

class Level3Window : public GameWindow
{
    Q_OBJECT

public:
    explicit Level3Window(QWidget* parent = nullptr);
    enum Room {
        ROOM_ONE, ROOM_TWO, ROOM_THREE, ROOM_FOUR,ROOM_FIVE,ROOM_SIX,ROOM_SEVEN
    };

signals:
    void GameCompleted();

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

#endif // LEVEL3WINDOW_H
