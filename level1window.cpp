#include "gamewindow.h"
#include "level1window.h"
#include "tile.h"
#include "level2window.h"
Level1Window::Level1Window(QWidget* parent) : GameWindow(parent)
{
    setWindowTitle("Level 1");
    m_currentRoom = ROOM_ONE;
    initializeGame();
}

void Level1Window::createTilesandWallsandCeiling() {
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
    case ROOM_TWO:
        setFundementals(0, 0, 4, 140,":/images/lvl1-scn2-back.png",":/images/lvl1-scn2-fore.png",406,0);
        createRoom2();
        break;
    case ROOM_THREE:
        setFundementals(0, 7, 2, 133,":/images/lvl1-scn3-back.png",":/images/lvl1-scn3-fore.png",550, 70);
        createRoom3();
        break;
    case ROOM_FOUR:
        setFundementals(0, 7, 2, 128, ":/images/lvl1-scn4-back.png", ":/images/lvl1-scn4-fore.png",540, 75);
        createRoom4();
        break;
    case ROOM_FIVE:
        setFundementals(0, 6, 2, 112, ":/images/lvl1-scn5-back.png", ":/images/lvl1-scn5-fore.png",556, 60);
        createRoom5();
        break;
    case ROOM_SIX:
        setFundementals(636, 154, 2, 128, ":/images/lvl1-scn6-back.png", ":/images/lvl1-scn6-fore.png",500, 70);
        createRoom6();
        break;
    case ROOM_SEVEN:
        setFundementals(638, 154, 2, 128, ":/images/lvl1-scn7-back.png", ":/images/lvl1-scn7-fore.png");
        createRoom7();
        break;
    case ROOM_EIGHT:
        setFundementals(258,176,114,144, ":/images/lvl1-scn8-back.png", ":/images/lvl1-scn8-fore.png");
        createRoom8();
        break;
    }

}

void Level1Window::createRoom1() {
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

void Level1Window::createRoom2() {
    QList<tile*> platform1 = createTiles(22, 292,1, 640, 5);
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(0, 130,1, 50, 5);
    m_tiles.append(platform2);

    QList<ceiling*> ceilings1 = createCeiling(146, 154, 256, 4);
    m_ceilings.append(ceilings1);
    QList<ceiling*> ceilings2 = createCeiling(530, 154, 128, 4);
    m_ceilings.append(ceilings2);
    QList<ceiling*> ceilings3 = createCeiling(408, 2, 4, 138);
    m_ceilings.append(ceilings3);

    QList<wall*> walls1 = createWalls(408, 2, 4, 138,false);
    m_walls.append(walls1);
    QList<wall*> walls2 = createWalls(636, 159, 4, 152,true);
    m_walls.append(walls2);
    QList<wall*> walls3 = createWalls(530, 7, 4, 147,true);
    m_walls.append(walls3);
    QList<wall*> walls4 = createWalls(146, 7, 4, 147,true);
    m_walls.append(walls4);
    QList<wall*> walls5 = createWalls(30, 159, 4, 128,false);
    m_walls.append(walls5);

}

void Level1Window::createRoom3() {
    QList<tile*> platform1 = createTiles(0, 140,3, 75, 5,false,0,QList<int>(),QList<int>{2},QList<int>{0});
    m_tiles.append(platform1);


    QList<tile*> platform2 = createTiles(278, 140, 1, 384, 5,false);
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(214, 444, 1, 128, 5,false,0,QList<int>{0});
    m_tiles.append(platform3);

    QList<wall*> walls3 = createWalls(636, 7, 4, 152,true);
    m_walls.append(walls3);

    connectPressureTileToGate(2,0);

    //QList<tile*> platform3 = createTiles(290, 140,1, 116, 38,false,0,QList<int>(),QList<int>{1});
    //m_tiles.append(platform3);


}

void Level1Window::createRoom4() {
    QList<tile*> platform1 = createTiles(390, 135, 3, 102, 5, false,0,QList<int>(),QList<int>{0});
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-16, 135, 1, 72, 5, false,0,QList<int>(),QList<int>(),QList<int>{0});
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(6, 282, 1, 242, 5, false);
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(327, 282, 4, 61, 5, false,0,QList<int>(),QList<int>{2});
    m_tiles.append(platform4);

    connectPressureTileToGate(7,0);

    QList<ceiling*> ceilings1 = createCeiling(404, 147, 192, 5);
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(0, 2, 640, 5);
    m_ceilings.append(ceilings2);

    QList<wall*> walls1 = createWalls(18, 160, 4, 122, false);
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(210, 305, 4, 122, false);
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(342, 305, 4, 122, true);
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(594, 173, 4, 108, true);
    m_walls.append(walls4);

    QList<wall*> walls5 = createWalls(636, 27, 4, 128, true);
    m_walls.append(walls5);
}

void Level1Window::createRoom5() {

    // Floors (x - 5, insert 1, width + 10)
    QList<tile*> platform1 = createTiles(406, 135,1, 256, 4); // [203, 59, 128, 2]
    m_tiles.append(platform1);
    QList<tile*> platform2 = createTiles(-5, 135, 1, 96, 5, false);  // [0, 59, 43, 2]
    m_tiles.append(platform2);
    QList<tile*> platform3 = createTiles(209, 135, 1, 74, 5, false,0,QList<int>(),QList<int>{0}); // [107, 59, 32, 2]
    m_tiles.append(platform3);
    QList<tile*> platform4 = createTiles(-5, 278, 1, 220, 5, false); // [0, 123, 105, 2]
    m_tiles.append(platform4);
    QList<tile*> platform5 = createTiles(278, 440, 1,64, 12, false,0,QList<int>{0}); // [0, 123, 105, 2]
    m_tiles.append(platform5);

    // Ceilings (unchanged)
    QList<ceiling*> ceilings1 = createCeiling(0, 2, 640, 5);         // [0, 1, 320, 2]
    m_ceilings.append(ceilings1);
    QList<ceiling*> ceilings2 = createCeiling(0, 148, 80, 5);        // [0, 65, 40, 2]
    m_ceilings.append(ceilings2);

    QList<wall*> walls1 = createWalls(210, 163, 4, 118, true);  // 153.43 +10 =163, 128.24 -10 =118
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(274, 149, 4, 278, false);  // 139.69 +10=149, 288.54-10=278
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(402, 149, 4, 288, true);  // 139.69 +10=149, 297.7 -10=288
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(636, 16, 4, 136, true);  // 6.87 +10=16.87 ≈16, 146.56 -10=136
    m_walls.append(walls4);

    QList<wall*> walls5 = createWalls(22, 170, 4, 111, true);  // 160.3 +10=170, 121.37 -10=111
    m_walls.append(walls5);


}
void Level1Window::createRoom6(){
    QList<tile*> platform1 = createTiles(342, 135, 1, 330, 5);
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(22, 135, 1, 74, 5);
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(22, 282, 1, 74, 5);
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(86, 428, 1, 330, 5);
    m_tiles.append(platform4);

    QList<tile*> platform5 = createTiles(322, 282, 1, 350, 5);
    m_tiles.append(platform5);

    // Ceilings (no adjustment)
    QList<ceiling*> ceiling1 = createCeiling(0, 2, 80, 5);
    m_ceilings.append(ceiling1);

    QList<ceiling*> ceiling2 = createCeiling(0, 149, 80, 5);
    m_ceilings.append(ceiling2);

    QList<ceiling*> ceiling3 = createCeiling(320, 2, 320, 5);
    m_ceilings.append(ceiling3);

    QList<ceiling*> ceiling4 = createCeiling(340, 149, 300, 5);
    m_ceilings.append(ceiling4);

    QList<ceiling*> ceiling5 = createCeiling(340, 296, 126, 5);
    m_ceilings.append(ceiling5);

    // Walls (apply y+10 and height-10)
    QList<wall*> wall1 = createWalls(18, 10, 4, 272, false);  // left_wall
    m_walls.append(wall1);

    QList<wall*> wall2 = createWalls(82, 296, 4, 132, false);  // left_wall
    m_walls.append(wall2);

    QList<wall*> wall3 = createWalls(466, 310, 4, 132, true);  // right_wall
    m_walls.append(wall3);

    QList<wall*> wall4 = createWalls(636, 16, 4, 137, true);  // right_wall
    m_walls.append(wall4);
}
void Level1Window::createRoom7(){
    QList<tile*> platform1 = createTiles(0, 282, 1, 50, 5);  // adjusted X to 0 instead of -5 to avoid negative coordinate
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(35, 282, 1, 650, 5,true);
    m_tiles.append(platform2);

    // Ceiling (no adjustment)
    QList<ceiling*> ceiling1 = createCeiling(0, 149, 640, 5);
    m_ceilings.append(ceiling1);

    // Walls (adjust Y + 10, height - 10)
    QList<wall*> wall1 = createWalls(0, 164, 4, 137, false);
    m_walls.append(wall1);
}
void Level1Window::createRoom8(){
    // Floors
    QList<tile*> platform1 = createTiles(6, 134, 1, 80, 5,false,0,QList<int>(),QList<int>{0});  // floor at (11,59,32,2) scaled and adjusted
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(6, 300, 1, 450, 5);  // floor at (11,59,32,2) scaled and adjusted
    m_tiles.append(platform2);

    addExit(258,176);

    connectPressureTileToGate(0,0);

    // Ceilings (unchanged except scaling)
    QList<ceiling*> ceilings1 = createCeiling(0, 2, 640, 4);
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(0, 150, 80, 4);
    m_ceilings.append(ceilings2);

    // Walls (+10 second val, -10 fourth val)
    QList<wall*> walls1 = createWalls(0, 133, 4, 284, true);   // right_wall (0,123,297,2)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(18, 23, 4, 46, false);   // left_wall (9,3,2,56)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(594, 23, 4, 110, true);  // right_wall (297,3,2,120)
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(0, 77, 4, 118, false);   // left_wall (0,67,2,64)
    m_walls.append(walls4);

}
void Level1Window::changeRoom(Room newRoom) {
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
void Level1Window::getNextRoom(){
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
        m_currentRoom=ROOM_EIGHT;
    }else if(m_currentRoom==ROOM_EIGHT){
        this->hide();
        Level2Window* newWindow = new Level2Window(this);
        newWindow->show();
    }
}
