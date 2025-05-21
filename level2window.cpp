#include "gamewindow.h"
#include "level2window.h"
#include "tile.h"

Level2Window::Level2Window(QWidget* parent) : GameWindow(parent)
{
    setWindowTitle("Level 2");
    m_currentRoom = ROOM_ONE;
    initializeGame();
}

void Level2Window::createTilesandWallsandCeiling() {
    for (Gate* gate : m_gates) {
        delete gate;
    }
    m_gates.clear();

    for (tile* t : m_tiles) delete t;
    m_tiles.clear();

    for(wall* w: m_walls) delete w;
    m_walls.clear();

    for(ceiling* c: m_ceilings) delete c;
    m_ceilings.clear();


    switch (m_currentRoom) {
    case ROOM_ONE:
        setFundementals(406, 458, 64, 4,":/images/lvl1-scn1-back.png",":/images/lvl1-scn1-fore.png");
        createRoom1();
        break;
    }

}

void Level2Window::createRoom1() {
    QList<tile*> platform1 = createTiles(-5, 130, 1, 50, 5, false);     // 0 -5 = -5, 40 +10 = 50
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(199, 140, 1, 350, 1);          // 204 -5 = 199, 340 +10 = 350
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(7, 292, 1, 286, 1);            // 12 -5 = 7, 276 +10 = 286
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(269, 444, 1, 138, 1);          // 274 -5 = 269, 128 +10 = 138
    m_tiles.append(platform4);

    QList<tile*> platform5 = createTiles(461, 444, 1, 138, 1);          // 466 -5 = 461, 128 +10 = 138
    m_tiles.append(platform5);


    QList<wall*> walls1 = createWalls(18, 143, 4, 147,false);
    m_walls.append(walls1);
    QList<wall*> walls2 = createWalls(274, 306, 4, 137,false);
    m_walls.append(walls2);
    QList<wall*> walls3 = createWalls(512, 7, 4, 133,true);
    m_walls.append(walls3);
    QList<wall*> walls4 = createWalls(338, 159, 4, 133,true);
    m_walls.append(walls4);
    QList<wall*> walls5 = createWalls(594, 312, 4, 133,true);
    m_walls.append(walls5);

    QList<ceiling*> ceilings1 = createCeiling(0, 0, 640, 7);
    m_ceilings.append(ceilings1);
    QList<ceiling*> ceilings2 = createCeiling(218, 154, 128, 4);
    m_ceilings.append(ceilings2);
    QList<ceiling*> ceilings3 = createCeiling(352, 306, 256, 4);
    m_ceilings.append(ceilings3);
    QList<ceiling*> ceilings4 = createCeiling(0, 2, 512, 4);
    m_ceilings.append(ceilings4);
    //QList<tile*> platform3 = createTiles(50, height() - 300, 5, 60,2, false, 28, QList<int>{1},QList<int>(),QList<int>(),QList<int>{4});
    //m_tiles.append(platform3);

    // Connect pressure tile to gate
    //connectPressureTileToGate(6, 0);
}

void Level2Window::changeRoom(Room newRoom) {
    if (m_currentRoom != newRoom) {
        m_currentRoom = newRoom;
        createTilesandWallsandCeiling();

        if (!m_tiles.isEmpty()) {
            tile* firstTile = m_tiles.first();
            int playerStartX = firstTile->pos().x() + 30;
            int playerStartY = firstTile->pos().y() - m_player->boundingRect().height();
            m_player->setPos(playerStartX, playerStartY);
        }

        update();
    }
}
void Level2Window::getNextRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_THREE;
    }else if(m_currentRoom == ROOM_THREE){
        m_currentRoom=ROOM_FOUR;
    }else if(m_currentRoom == ROOM_FOUR){
        m_currentRoom=ROOM_FIVE;
    }else if(m_currentRoom == ROOM_FIVE){
        m_currentRoom=ROOM_SIX;
    }else if(m_currentRoom == ROOM_SIX){
        m_currentRoom=ROOM_SEVEN;
    }
}
