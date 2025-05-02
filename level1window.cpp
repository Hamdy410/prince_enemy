#include "gamewindow.h"
#include "level1window.h"
#include "tile.h"

Level1Window::Level1Window(QWidget* parent) : GameWindow(parent)
{
    setWindowTitle("Level 1");
    initializeGame();
}

void Level1Window::createTiles() {
    for (tile* t : m_tiles) delete t;
    m_tiles.clear();

    QList<tile*> platform1 = createTiles(100, height() - 100, 10, 60, true, 28, QList<int>(), QList<int>{6});
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(400, height() - 200, 3, 60, true, 28, QList<int>());
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(50, height() - 300, 5, 60, false, 28, QList<int>{1, 4});
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(50, height() - 200, 3, 60, false, 28, QList<int>(), QList<int>{1});
    m_tiles.append(platform4);
}
