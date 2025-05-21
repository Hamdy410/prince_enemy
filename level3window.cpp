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
        setFundementals(0, 0, 5, 100, ":/images/lvl3-scn1-back.png", ":/images/lvl3-scn1-fore.png",258,220);
        createRoom1();
        break;
    case ROOM_TWO:
        setFundementals(0, 0, 5, 400, ":/images/lvl3-scn2-back.png", ":/images/lvl3-scn2-fore.png");
        createRoom2();
        break;
    case ROOM_THREE:
        setFundementals(0, 2, 4, 435, ":/images/lvl3-scn3-back.png", ":/images/lvl3-scn3-fore.png",600,200);
        createRoom3();
        break;
    case ROOM_FOUR:
        setFundementals(0, 150, 4, 130, ":/images/lvl3-scn3-back.png", ":/images/lvl3-scn3-fore.png");
        createRoom4();
    }

}

void Level3Window::createRoom1() {
    QList<tile*> platform1 = createTiles(76, 296, 1, 468, 5);   // floor (43,123,224)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-10, 138, 1, 116, 5);  // floor (0,59,43)
    m_tiles.append(platform2);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(0, 2, 256, 4);    // ceiling (0,1,128)
    m_ceilings.append(ceilings1);

    // Walls
    QList<wall*> walls1 = createWalls(82, 162, 4, 128, false);  // left_wall (41,61,2,64)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(522, 36, 4, 256, true);    // right_wall (261,3,2,128)
    m_walls.append(walls2);
}
void Level3Window::createRoom2() {
    QList<tile*> platform1 = createTiles(551, 135, 2, 42, 5,false,0,QList<int>(),QList<int>{0});   // (299,59,21)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-10, 282, 6, 72, 5,false,0,QList<int>{2,3});  // (0,123,80)
    m_tiles.append(platform2);
    QList<tile*> platform3 = createTiles(268, 135, 1, 80, 5);  // (139,59,32)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(80, 135, 1, 80, 5);  // (139,59,32)
    m_tiles.append(platform4);

    // Walls
    QList<wall*> walls1 = createWalls(402, 313, 4, 191, false);  // left_wall (201,125,2,62) scaled and adjusted
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(594, 149, 4, 275, true);   // right_wall (299,61,2,120)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(636, 20, 4, 162, true);     // right_wall (318,0,2,70)
    m_walls.append(walls3);

    // Ceilings (scaled)
    QList<ceiling*> ceilings1 = createCeiling(0, 2, 640, 4);     // ceiling (0,1,320)
    m_ceilings.append(ceilings1);
}
void Level3Window::createRoom3() {
    QList<tile*> platform1 = createTiles(90, 282, 1, 582, 5,true);
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-10, 135, 1, 234, 5);
    m_tiles.append(platform2);

    // Ceilings
    QList<ceiling*> ceiling1 = createCeiling(0, 2, 256, 4);
    m_ceilings.append(ceiling1);

    QList<ceiling*> ceiling2 = createCeiling(274, 149, 362, 4);
    m_ceilings.append(ceiling2);

    QList<ceiling*> ceiling3 = createCeiling(144, 149, 64, 4);
    m_ceilings.append(ceiling3);

    // Walls
    QList<wall*> wall1 = createWalls(82, 173, 4, 137, false);
    m_walls.append(wall1);

    QList<wall*> wall2 = createWalls(274, 12, 4, 137, true);
    m_walls.append(wall2);

}
void Level3Window::createRoom4(){
    // Platforms (scaled floors)
    /*
    QList<tile*> platform1 = createTiles(516, 135, 1, 124, 5);  // Original: 258,59,62,2
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(406, 135, 1, 66, 5);   // Original: 203,59,33,2
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(0, 282, 1, 320, 5);    // Original: 0,123,160,2
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(342, 429, 1, 64, 5);   // Original: 171,187,32,2
    m_tiles.append(platform4);

    // Walls (scaled and typed)
    QList<wall*> walls1 = createWalls(146, 2, 4, 147, false);  // Left wall (73,1,2,64)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(242, 397, 4, 142, false); // Left wall (121,173,2,62)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(342, 433, 4, 284, true);  // Right wall (171,189,2,124)
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(636, 2, 4, 147, true);    // Right wall (318,1,2,64)
    m_walls.append(walls4);

    // Adjusted ceilings
    QList<ceiling*> ceilings1 = createCeiling(-10, 159, 160, -5);  // Original: 0,65,70,2
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(310, 12, 340, -5);   // Original: 160,1,160,2
    m_ceilings.append(ceilings2);
    */
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
