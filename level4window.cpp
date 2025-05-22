#include "gamewindow.h"
#include "level4window.h"
#include "level5window.h"
#include "tile.h"
#include <QMessageBox>
Level4Window::Level4Window(QWidget* parent, int healthVal, int scoreVal) : GameWindow(parent,healthVal,scoreVal)
{
    setWindowTitle("Level 4");
    m_currentRoom = ROOM_ONE;
    initializeGame();
}

void Level4Window::createTilesandWallsandCeiling() {
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
        setFundementals(600, 300, 10, 110, ":/images/lvl4-scn1-back.png", ":/images/lvl4-scn1-fore.png");
        createRoom1();
        break;
    case ROOM_TWO:
        setFundementals(214, 30, 128, 20, ":/images/lvl4-scn2-back.png", ":/images/lvl4-scn2-fore.png");
        createRoom2();
        break;
    case ROOM_THREE:
        setFundementals(0, 0, 5, 100, ":/images/lvl4-scn3-back.png", ":/images/lvl4-scn3-fore.png");
        createRoom3();
        break;
    case ROOM_FOUR:
        setFundementals(322, 120, 114, 145, ":/images/lvl4-scn6-back.png", ":/images/lvl4-scn6-fore.png");
        createRoom4();
    }

}

void Level4Window::createRoom1() {
    // Platforms
    QList<tile*> platform1 = createTiles(396, 440, 1, 254, 5);   // floor (203,187,117)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(12, 440, 1, 340, 5);    // floor (11,187,160)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(76, 276, 1, 84, 5);     // floor (43,123,32)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(204, 276, 1, 212, 5);   // floor (107,123,96)
    m_tiles.append(platform4);

    QList<tile*> platform5 = createTiles(140, 148, 1, 148, 5);   // floor (75,59,64)
    m_tiles.append(platform5);

    QList<tile*> platform6 = createTiles(460, 148, 1, 148, 5);   // floor (235,59,64)
    m_tiles.append(platform6);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(0, 32, 640, 4);         // ceiling (0,1,320)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(86, 298, 256, 4);       // ceiling (43,129,128)
    m_ceilings.append(ceilings2);

    QList<ceiling*> ceilings3 = createCeiling(214, 170, 60, 4);       // ceiling (107,65,30)
    m_ceilings.append(ceilings3);

    QList<ceiling*> ceilings4 = createCeiling(470, 170, 128, 4);      // ceiling (235,65,64)
    m_ceilings.append(ceilings4);

    // Walls
    QList<wall*> walls1 = createWalls(0, 62, 4, 374, true);           // left_wall (0,11,2,192)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(214, 170, 4, 118, true);        // left_wall (107,65,2,64)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(402, 298, 4, 118, true);        // left_wall (201,129,2,64)
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(152, 174, 4, 110, false);       // right_wall (76,67,2,60)
    m_walls.append(walls4);

    QList<wall*> walls5 = createWalls(342, 302, 4, 110, false);       // right_wall (171,131,2,60)
    m_walls.append(walls5);

    QList<wall*> walls6 = createWalls(598, 32, 4, 118, false);        // right_wall (299,1,2,64)
    m_walls.append(walls6);
}

void Level4Window::createRoom2() {
    // Platforms
    QList<tile*> platform1 = createTiles(-6, 424, 1, 186, 5);       // floor (2,187,73)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(120, 276, 7, 80, 5,false,9,QList<int>(),QList<int>(),QList<int>(),QList<int>{1,3,5});      // floor (75,123,245)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(204, 148, 1, 200, 5);      // floor (107,59,96)
    m_tiles.append(platform3);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(320, 32, 320, 4);     // ceiling (160,1,160)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(0, 148, 380, 4);      // ceiling (0,165,200)
    m_ceilings.append(ceilings2);

    // Walls
    QList<wall*> walls1 = createWalls(0, 40, 4, 374, true);         // left_wall (0,0,2,192)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(636, 40, 4, 374, false);      // right_wall (318,0,2,192)
    m_walls.append(walls2);

}
void Level4Window::createRoom3() {
    QList<tile*> platform1 = createTiles(340, 267, 3, 76, 5,false,0,QList<int>(),QList<int>{1});   // floor (171,187,64)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(10, 140, 1, 70, 5,false,0,QList<int>(),QList<int>(),QList<int>{0});     // floor (0,59,203)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(80, 140, 1, 172, 5,true);     // floor (0,59,203)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(252, 140, 1, 173, 5,true);     // floor (0,59,203)
    m_tiles.append(platform4);


    connectPressureTileToGate(1,0);
    QList<ceiling*> ceiling1 = createCeiling(0, 1, 640, 2);         // ceiling (0,1,320)
    m_ceilings.append(ceiling1);

    QList<wall*> wall1 = createWalls(214, 168, 4, 285, false);      // left_wall (107,69,2,124)
    m_walls.append(wall1);

    QList<wall*> wall2 = createWalls(340, 313, 4, 138, false);      // left_wall (170,132,2,60)
    m_walls.append(wall2);

    QList<wall*> wall3 = createWalls(466, 311, 4, 138, true);       // right_wall (233,131,2,60)
    m_walls.append(wall3);

    QList<wall*> wall4 = createWalls(594, 12, 4, 294, true);        // right_wall (297,1,2,128)
    m_walls.append(wall4);

}
void Level4Window::createRoom4() {
    QList<tile*> platform1 = createTiles(0, 430, 2, 90, 5,false,0,QList<int>(),QList<int>{1});  // floor (0,187,75)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(140, 283, 1, 458, 5);  // floor (75,123,224)
    m_tiles.append(platform2);

    // Walls
    QList<wall*> wall1 = createWalls(0, 299, 4, 138, false);  // left_wall (0,130,2,60)
    m_walls.append(wall1);

    QList<wall*> wall2 = createWalls(160, 301, 4, 138, true);  // right_wall (75,131,2,60)
    m_walls.append(wall2);

    QList<wall*> wall3 = createWalls(596, 7, 4, 294, true);  // right_wall (298,3,2,128)
    m_walls.append(wall3);

    addExit(322,170);

    connectPressureTileToGate(1,0);

}
void Level4Window::getNextRoom(){
    if(m_currentRoom==ROOM_ONE){
        m_currentRoom=ROOM_TWO;
    }else if(m_currentRoom == ROOM_TWO){
        m_currentRoom=ROOM_THREE;
    }else if(m_currentRoom == ROOM_THREE){
        m_currentRoom=ROOM_FOUR;
    }else if(m_currentRoom == ROOM_FOUR){
        QMessageBox::information(this,"well done","you passed lvl4");
        Level5Window* newWind = new Level5Window(this,total_health,total_score);
        newWind->show();
        this->hide();
    }

}
void Level4Window::getCurrentRoom(){
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
