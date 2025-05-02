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

    QList<tile*> platform1 = createTiles(100, height() - 100, 10, 60, true, 28, QList<int>(), QList<int>{6});
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(400, height() - 200, 3, 60, true, 28, QList<int>(), QList<int>(), QList<int>{2});
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(50, height() - 300, 5, 60, false, 28, QList<int>{1, 4});
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(50, height() - 200, 3, 60, false, 28, QList<int>(), QList<int>{1});
    m_tiles.append(platform4);

    // Connect ONLY the first pressure tile to the first gate
    // The global index of the first pressur tile is 2 (it's at index 2 in platform 1)
    connectPressureTileToGate(6, 0);

    // The other pressure tiles (at index 7 in platform 1 and index 1 in platform 2)
    // are not connected to any gates, so they'll be "fake"
}
