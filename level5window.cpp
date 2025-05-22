#include "gamewindow.h"
#include "level5window.h"
#include "tile.h"
#include<QMessageBox>
Level5Window::Level5Window(QWidget* parent, int healthVal, int scoreVal) : GameWindow(parent,healthVal,scoreVal)
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
        setFundementals(636, 0, 4, 128, ":/lvl5-scn1-back.png", ":/lvl5-scn1-fore.png",220,200);
        createRoom1();
        break;
    case ROOM_TWO:
        setFundementals(25, 312, 4, 571, ":/lvl5-scn2-back.png", ":/lvl5-scn2-fore.png");
        createRoom2();
        break;
    case ROOM_THREE:
        setFundementals(194, 120, 114, 145, ":/lvl5-scn6-back.png", ":/lvl5-scn6-fore.png");
        createRoom3();
        break;
    }
}

void Level5Window::createRoom1() {
    // Floors
    QList<tile*> platform1 = createTiles(22, 280, 7, 64, 5,false,0,QList<int>{5});    // floor (11,123,224)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(440, 130, 3, 73, 5,false,0,QList<int>(),QList<int>(),QList<int>(),QList<int>{1});    // floor (235,59,85)
    m_tiles.append(platform2);

    // Ceiling
    QList<ceiling*> ceilings1 = createCeiling(0, 1, 640, 2);     // ceiling (0,1,320)
    m_ceilings.append(ceilings1);

    // Walls
    QList<wall*> walls1 = createWalls(18, 114, 4, 874, false);   // left_wall (9,0,2,190), y scaled +10
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(460, 200, 4, 294, true);   // right_wall (235,61,2,64), y scaled +10
    m_walls.append(walls2);
}

void Level5Window::createRoom2(){
    QList<tile*> platform1 = createTiles(0, 139, 1, 214, 5,true);         // floor (0,59,107)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(22, 430, 1, 220, 5,true);       // floor (11,123,96)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(22, 267, 1, 210, 5,true);       // floor (11,187,96)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(342, 139, 1, 256, 5,true);       // floor (171,59,128) (note floor type 1 remains 1)
    m_tiles.append(platform4);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(0, 1, 640, 2);        // ceiling (0,1,320)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(0, 159, 214, 2);         // floor (0,59,107)
    m_ceilings.append(ceilings2);

    QList<ceiling*> ceilings3 = createCeiling(22, 450, 220, 2);       // floor (11,123,96)
    m_ceilings.append(ceilings3);

    QList<ceiling*> ceilings4 = createCeiling(22, 307, 210, 2);       // floor (11,187,96)
    m_ceilings.append(ceilings4);

    QList<ceiling*> ceilings5 = createCeiling(342, 159, 256, 2);       // floor (171,59,128) (note floor type 1 remains 1)
    m_ceilings.append(ceilings5);

    // Walls
    QList<wall*> walls1 = createWalls(0, 10, 2, 64, false);          // left_wall (0,0,1,64)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(18, 312, 4, 571, false);       // left_wall (9,67,2,124) y*4.6 + 10
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(18, 150, 4, 571, true);       // right_wall (173,67,2,124) y*4.6 + 10
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(598, 20, 4, 294, true);        // right_wall (299,2,2,64) y*4.6 + 10
    m_walls.append(walls4);
}
void Level5Window::createRoom3(){
    //Floors
    QList<tile*> platform1 = createTiles(544, 300, 2, 45, 5,false,0,QList<int>(),QList<int>{0});       // floor (267,123,32)
    m_tiles.append(platform1);
    QList<tile*> platform2 = createTiles(380, 140, 1, 168, 5);       // floor (203,59,64)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(160, 273, 1, 128, 5);      // floor (75,123,64)
    m_tiles.append(platform3);

    addExit(194, 164);

    connectPressureTileToGate(0,0);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(0, 1, 640, 2);        // ceiling (0,1,320)
    m_ceilings.append(ceilings1);

    // Walls
    QList<wall*> walls1 = createWalls(0, 30, 4, 437, false);        // left_wall (0,9,2,190)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(276, 313, 4, 156, false);     // left_wall (138,127,2,68)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(532, 166, 4, 147, false);     // left_wall (266,63,2,64)
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(160, 326, 4, 143, true);      // right_wall (75,132,2,62)
    m_walls.append(walls4);

    QList<wall*> walls5 = createWalls(406, 176, 4, 285, true);      // right_wall (203,68,2,124)
    m_walls.append(walls5);


}
void Level5Window::getNextRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_THREE;
    }else if(m_currentRoom == ROOM_THREE){
        this->hide();
        emit gameCompleted();
    }
}
void Level5Window::getCurrentRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_ONE;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_THREE){
        m_currentRoom=ROOM_THREE;
    }
}
