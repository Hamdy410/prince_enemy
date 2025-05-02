#include "gamewindow.h"
#include "level1window.h"
#include "tile.h"

Level1Window::Level1Window(QWidget* parent) : GameWindow(parent)
{
    setWindowTitle("Level 1");
    initializeGame();
}

void Level1Window::createTiles() {
    for (Gate* gate : m_gates) {
        delete gate;
    }
    m_gates.clear();

    for (tile* t : m_tiles) delete t;
    m_tiles.clear();

    switch (m_currentRoom) {
    case ROOM_ONE:
        createRoom1();
        break;
    case ROOM_TWO:
        createRoom2();
        break;
    case ROOM_THREE:
        createRoom3();
        break;
    case ROOM_FOUR:
        createRoom4();
        break;
    }
}

void Level1Window::createRoom1() {
    QList<tile*> platform1 = createTiles(100, height() - 100, 10, 60, true, 28, QList<int>(), QList<int>{6});
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(400, height() - 200, 3, 60, true, 28, QList<int>(), QList<int>(), QList<int>{2});
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(50, height() - 300, 5, 60, false, 28, QList<int>{1, 4});
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(50, height() - 200, 3, 60, false, 28, QList<int>(), QList<int>{1});
    m_tiles.append(platform4);

    // Connect pressure tile to gate
    connectPressureTileToGate(6, 0);
}

void Level1Window::createRoom2() {
    QList<tile*> floor = createTiles(50, height() - 100, 15, 60, false, 28);
    m_tiles.append(floor);

    QList<tile*> platform1 = createTiles(200, height() - 200, 5, 60, true, 28);
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(400, height() - 300, 3, 60, false, 28, QList<int>{1});
    m_tiles.append(platform2);
}

void Level1Window::createRoom3() {
    QList<tile*> floor = createTiles(50, height() - 100, 20, 60, false, 28);
    m_tiles.append(floor);

    QList<tile*> platform = createTiles(300, height() - 250, 4, 60, true, 28);
    m_tiles.append(platform);

    QList<tile*> exitPlatform = createTiles(550, height() - 100, 3, 60, false, 28, QList<int>(), QList<int>(), QList<int>{1});
    m_tiles.append(exitPlatform);
}

void Level1Window::createRoom4() {
    QList<tile*> platform1 = createTiles(100, height() - 150, 8, 60, false, 28);
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(200, height() - 250, 4, 60, false, 28, QList<int>(), QList<int>{2});
    m_tiles.append(platform2);

    // Special gate that reveals a hidden passage
    QList<tile*> secretPlatform = createTiles(400, height() - 350, 3, 60, false, 28, QList<int>(), QList<int>(), QList<int>{1});
    m_tiles.append(secretPlatform);

    connectPressureTileToGate(10, 0); // Connect pressure tile to gate
}

void Level1Window::changeRoom(Room newRoom) {
    if (m_currentRoom != newRoom) {
        m_currentRoom = newRoom;
        createTiles();

        if (!m_tiles.isEmpty()) {
            tile* firstTile = m_tiles.first();
            int playerStartX = firstTile->pos().x() + 30;
            int playerStartY = firstTile->pos().y() - m_player->boundingRect().height();
            m_player->setPos(playerStartX, playerStartY);
        }

        update();
    }
}
