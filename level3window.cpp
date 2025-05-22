#include "gamewindow.h"
#include "level3window.h"
#include "tile.h"
#include "level4window.h"
#include<QMessageBox>
Level3Window::Level3Window(QWidget* parent, int healthVal, int scoreVal) : GameWindow(parent,healthVal,scoreVal)
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
        setFundementals(0, 134, 4, 134, ":/images/lvl3-scn4-back.png", ":/images/lvl3-scn4-fore.png");
        createRoom4();
        break;
    case ROOM_FIVE:
        setFundementals(66, 104, 114, 144, ":/images/lvl3-scn7-back.png", ":/images/lvl3-scn7-fore.png");
        createRoom5();
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

    Coin* coin1 = new Coin(QPointF(30, 118),10);
    m_coins.append(coin1);
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

    Coin* coin2 = new Coin(QPointF(268, 115),10);
    m_coins.append(coin2);
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
    Coin* coin3 = new Coin(QPointF(130, 262),10);
    m_coins.append(coin3);
}
void Level3Window::createRoom4(){
    // Floors as platforms (x*2, y*2.288, width*2, height*2.288 approx)
    QList<tile*> platform1 = createTiles(516, 135, 1, 142, 5);  // floor (258,59,62,2)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(406, 135, 1, 76, 5,false,0);   // floor (203,59,33,2)
    m_tiles.append(platform2);


    QList<tile*> platform3 = createTiles(0, 282, 5, 74, 5,false,0,QList<int>(),QList<int>{4},QList<int>{1},QList<int>{3});    // floor (0,123,160,2)
    m_tiles.append(platform3);

    connectPressureTileToGate(6,0);
    // Spikes (death) as tile
    QList<tile*> spikes1 = createTiles(472, 135, 1, 50, 5,false,0,QList<int>{0});     // death (236,59,22,2)
    m_tiles.append(spikes1);

    // Walls (x*2, y*2.288, width*2, height*2.288)
    QList<wall*> walls1 = createWalls(146, 2, 4, 147, true);   // left_wall (73,1,2,64)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(636, 2, 4, 147, true);    // right_wall (318,1,2,64)
    m_walls.append(walls2);


    // Ceilings with adjustments:
    // Original ceiling: (0,65,70,2)
    // Adjusted ceiling: x-10= -10, y+10=75, width+20=90, height-10=-8 (approximate)
    QList<ceiling*> ceilings1 = createCeiling(-10, 149, 90, -8);   // ceiling (0,65,70,2) scaled and adjusted
    m_ceilings.append(ceilings1);

    // Original ceiling: (160,1,160,2)
    // Adjusted ceiling: x-10=150, y+10=23, width+20=180, height-10=-8 (approximate)
    QList<ceiling*> ceilings2 = createCeiling(310, 23, 180, -8);   // ceiling (160,1,160,2) scaled and adjusted
    m_ceilings.append(ceilings2);

}
void Level3Window::createRoom5(){
    // Platforms (floors)
    QList<tile*> platform1 = createTiles(588, 276, 1, 42, 5);  // (299,123,21)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(350, 434, 1, 424, 5);  // (139,187,192)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(0, 276, 7, 61, 5,false,0,QList<int>(),QList<int>{6});  // (0,123,203)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(194, 148, 1, 158, 5);  // (107,59,64)
    m_tiles.append(platform4);

    // Ceilings
    QList<ceiling*> ceiling1 = createCeiling(0, 32, 640, 4);  // (0,1,320)
    m_ceilings.append(ceiling1);

    QList<ceiling*> ceiling2 = createCeiling(210, 170, 124, 4);  // (105,65,62)
    m_ceilings.append(ceiling2);

    QList<ceiling*> ceiling3 = createCeiling(256, 288, 144, 4);  // (128,129,72)
    m_ceilings.append(ceiling3);

    QList<ceiling*> ceiling4 = createCeiling(594, 288, 46, 4);  // (297,129,23)
    m_ceilings.append(ceiling4);

    // Exit
    addExit(66,170);
    connectPressureTileToGate(8,0);

    // Wall
    QList<wall*> wall1 = createWalls(0, 40, 4, 370, false);  // (0,0,2,190)
    m_walls.append(wall1);

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
        this->hide();
        emit Level4Requested();
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
    }
}
