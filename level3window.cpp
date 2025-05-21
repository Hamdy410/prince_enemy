#include "gamewindow.h"
#include "level3window.h"
#include "tile.h"

Level3Window::Level3Window(QWidget* parent) : GameWindow(parent)
{
    setWindowTitle("Level 3");
    m_currentRoom = ROOM_ONE;
    initializeGame();
}

void Level3Window::createTilesandWallsandCeiling() {
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
        setFundementals(0, 0, 4, 282, ":/images/lvl2-scn1-back.png", ":/images/lvl2-scn1-fore.png",240, 212);
        createRoom1();
        break;
    }

}

void Level3Window::createRoom1() {
    QList<tile*> platform1 = createTiles(-10, 282, 1, 500, 5);  // (0,123,235,2)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(475, 444, 1, 138, 5);  // (240,187,64,2)
    m_tiles.append(platform2);

    // Walls (adjusted: +10 to y, -10 from height)
    QList<wall*> walls1 = createWalls(466, 290, 4, 144, false); // (233,125,2,62)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(576, 164, 4, 242, true);  // (288,62,2,126)
    m_walls.append(walls2);
}

void Level3Window::getNextRoom(){
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
    }else if(m_currentRoom == ROOM_SEVEN){

    }
}
void Level3Window::getCurrentRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_ONE;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_THREE){
        m_currentRoom=ROOM_THREE;
    }else if(m_currentRoom == ROOM_FOUR){
        m_currentRoom=ROOM_FOUR;
    }else if(m_currentRoom == ROOM_FIVE){
        m_currentRoom=ROOM_FIVE;
    }else if(m_currentRoom == ROOM_SIX){
        m_currentRoom=ROOM_SIX;
    }else if(m_currentRoom == ROOM_SEVEN){
        m_currentRoom=ROOM_SEVEN;
    }
}
