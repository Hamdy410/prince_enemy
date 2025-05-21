#include "gamewindow.h"
#include "level2window.h"
#include "level3window.h"
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
        setFundementals(0, 0, 4, 282, ":/images/lvl2-scn1-back.png", ":/images/lvl2-scn1-fore.png",240, 212);
        createRoom1();
        break;
    case ROOM_TWO:
        setFundementals(0, 0, 4, 282, ":/images/lvl2-scn2-back.png", ":/images/lvl2-scn2-fore.png");

        createRoom2();
        break;
    case ROOM_THREE:
        setFundementals(0, 0, 2, 123, ":/images/lvl2-scn3-back.png", ":/images/lvl2-scn3-fore.png", 500, 200);
        createRoom3();
        break;
    case ROOM_FOUR:
        setFundementals(100, 0, 128, 22, ":/images/lvl2-scn4-back.png", ":/images/lvl2-scn4-fore.png",550 , 60);
        createRoom4();
        break;
    case ROOM_FIVE:
        setFundementals(0, 134, 4, 128, ":/images/lvl2-scn5-back.png", ":/images/lvl2-scn5-fore.png");
        createRoom5();
        break;
    case ROOM_SIX:
        setFundementals(0, 4, 4, 128, ":/images/lvl2-scn6-back.png", ":/images/lvl2-scn6-fore.png",560, 200);
        createRoom6();
        break;
    case ROOM_SEVEN:
        setFundementals(258, 171,114,144, ":/images/lvl2-scn7-back.png", ":/images/lvl2-scn7-fore.png");
        createRoom7();
    }

}

void Level2Window::createRoom1() {
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
void Level2Window::createRoom2() {
    QList<tile*> platform1 = createTiles(593, 276, 1, 52, 5);  // (299,123,21)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-5, 276, 1, 500, 5,true);  // (0,123,235)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(475, 438, 1, 138, 5); // (240,187,64)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(145, 438, 1, 458, 5); // (75,187,224)
    m_tiles.append(platform4);

    // Walls
    QList<wall*> walls1 = createWalls(594, 312, 4, 137, true);  // (297,131,2,64)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(86, 312, 4, 137, false);  // (43,131,2,64)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(636, 40, 4, 447, true);   // (318,0,2,200)
    m_walls.append(walls3);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(76, 308, 404, 2);  // (43,129,192)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(-10, 170, 100, 2); // (0,65,40)
    m_ceilings.append(ceilings2);
}
void Level2Window::createRoom3() {
    QList<tile*> platform1 = createTiles(401, 276, 1, 254, 5);  // (203,123,117)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-5, 130, 1, 180, 5);   // (0,59,75)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(-5, 276, 6, 60, 5,false,0,QList<int>{5});   // (0,123,171)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(337, 438, 1, 276, 5);  // (171,187,128)
    m_tiles.append(platform4);

    // Walls
    QList<wall*> walls1 = createWalls(342, 312, 4, 137, false); // (171,125,2,62)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(594, 324, 4, 137, true);  // (297,132,2,62)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(274, 46, 4, 137, true);   // (137,3,2,62)
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(594, 312, 4, 137, true);  // (297,131,2,62)
    m_walls.append(walls4);

    QList<wall*> walls5 = createWalls(636, 40, 4, 447, true);   // (318,0,2,200)
    m_walls.append(walls5);

    // Ceilings
    QList<ceiling*> ceilings1 = createCeiling(-10, 50, 660, 2);    // (0,1,320)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(-10, 170, 164, 2);   // (0,65,72)
    m_ceilings.append(ceilings2);

    QList<ceiling*> ceilings3 = createCeiling(264, 170, 386, 2);   // (137,65,183)
    m_ceilings.append(ceilings3);

    QList<ceiling*> ceilings4 = createCeiling(392, 308, 212, 2);   // (201,129,96)
    m_ceilings.append(ceilings4);
}
void Level2Window::createRoom4(){
    QList<tile*> platform1 = createTiles(268, 135, 1, 382, 5); // (139,59,181)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(76, 135, 1, 148, 5); // (43,59,64)
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(268, 281, 1, 382, 5); // (139,123,181)
    m_tiles.append(platform3);

    QList<tile*> platform4 = createTiles(136, 428, 1, 148, 5); // (73,187,64)
    m_tiles.append(platform4);

    // Ceilings (unchanged)
    QList<ceiling*> ceilings1 = createCeiling(64, 2, 80, 4); // (32,1,40,2)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(256, 2, 384, 4); // (128,1,192,2)
    m_ceilings.append(ceilings2);

    QList<ceiling*> ceilings3 = createCeiling(274, 148, 362, 4); // (137,65,181,2)
    m_ceilings.append(ceilings3);

    // Walls (Y +10, H -10)
    QList<wall*> walls1 = createWalls(84, 33, 4, 24, false); // (42,3,2,64)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(146, 165, 4, 232, false); // (73,61,2,126)
    m_walls.append(walls2);

    QList<wall*> walls3 = createWalls(274, 315, 4, 87, true); // (137,129,2,60)
    m_walls.append(walls3);

    QList<wall*> walls4 = createWalls(636, 30, 4, 410, true); // (318,0,2,192)
    m_walls.append(walls4);
}
void Level2Window::createRoom5(){
    QList<tile*> platform1 = createTiles(76, 429, 1, 106, 5); // (43,187,2)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-10, 282, 1, 110, 5); // (0,123,43)
    m_tiles.append(platform2);

    // Walls
    QList<wall*> wall1 = createWalls(82, 297, 4, 132, false); // (41,125,2,62)
    m_walls.append(wall1);

    QList<wall*> wall2 = createWalls(140, 10, 4, -5, true); // (70,0,194,2) - note: invalid height (-5)
    m_walls.append(wall2); // You may want to handle this edge case manually

    // Ceilings
    QList<ceiling*> ceiling1 = createCeiling(0, 149, 256, 5); // (0,65,128,2)
    m_ceilings.append(ceiling1);
}
void Level2Window::createRoom6(){
    QList<tile*> platform1 = createTiles(12, 276, 10, 60, 5,true,0,QList<int>(),QList<int>{1});  // (11,123,288) → (22-10,246,576+20)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(-10, 118, 1, 60, 5,false,0,QList<int>(),QList<int>(),QList<int>{0});  // (0,59,11) → (0-10,118,22+20)
    m_tiles.append(platform2);


    QList<wall*> walls1 = createWalls(146, 2, 4, 124, true);   // (73,1,2,62)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(636, 0, 4, 388, true);   // (318,0,2,194)
    m_walls.append(walls2);
    QList<ceiling*> ceilings1 = createCeiling(0, 2, 128, 2);   // (0,1,64,2)
    m_ceilings.append(ceilings1);

    QList<ceiling*> ceilings2 = createCeiling(128, 130, 512, 2); // (64,65,256,2)
    m_ceilings.append(ceilings2);

    connectPressureTileToGate(1,0);

}
void Level2Window::createRoom7(){
    QList<tile*> platform1 = createTiles(524, 118, 1, 146, 5);  // (267,59,53) → (534-10,118,106+20)
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(76, 270, 7, 65, 5,false,0,QList<int>(),QList<int>{0});   // (43,123,224) → (86-10,246,448+20)
    m_tiles.append(platform2);
    QList<wall*> walls1 = createWalls(86, 2, 4, 256, false);    // (43,1,2,128)
    m_walls.append(walls1);

    QList<wall*> walls2 = createWalls(530, 136, 4, 128, true);  // (265,68,2,64)
    m_walls.append(walls2);
    addExit(258, 171);  // (129,52,57,63)
    connectPressureTileToGate(1,0);
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
    }else if(m_currentRoom == ROOM_SEVEN){
        this->hide();
        Level3Window* nextWindow = new Level3Window(this);
        nextWindow->show();
    }
}
void Level2Window::getCurrentRoom(){
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
