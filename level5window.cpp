#include "gamewindow.h"
#include "level5window.h"
#include "tile.h"

Level5Window::Level5Window(QWidget* parent) : GameWindow(parent)
{
    setWindowTitle("Level 5");
    m_currentRoom = ROOM_ONE;
    initializeGame();
}

void Level5Window::createTilesandWallsandCeiling() {
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
        setFundementals(636, 0, 4, 64, ":/lvl5-scn1-back.png", ":/lvl5-scn1-fore.png");
        createRoom1();
        break;
    }
}

void Level5Window::createRoom1() {
    // Floors
    QList<tile*> platform1 = createTiles(22, 280, 1, 448, 5);    // floor (11,123,224)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(470, 59, 1, 170, 5);    // floor (235,59,85)
    m_tiles.append(platform2);

    // Ceiling
    QList<ceiling*> ceilings1 = createCeiling(0, 1, 640, 2);     // ceiling (0,1,320)
    m_ceilings.append(ceilings1);

    // Walls
    QList<wall*> walls1 = createWalls(18, 114, 4, 874, false);   // left_wall (9,0,2,190), y scaled +10
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(470, 288, 4, 294, true);   // right_wall (235,61,2,64), y scaled +10
    m_walls.append(walls2);
}

void Level5Window::getNextRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_THREE;
    }else if(m_currentRoom == ROOM_THREE){
        m_currentRoom=ROOM_FOUR;
    }else if(m_currentRoom == ROOM_FOUR){
    }
}
void Level5Window::getCurrentRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_ONE;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_THREE){
        m_currentRoom=ROOM_THREE;
    }else if(m_currentRoom == ROOM_FOUR){
        m_currentRoom=ROOM_FOUR;
    }
}
