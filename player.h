#ifndef PLAYER_H
#define PLAYER_H
#include "score.h"
#include<QGraphicsTextItem>
#include<QGraphicsItem>
#include<QObject>
#include<QGraphicsPixmapItem>
#include<QGraphicsRectItem>
#include<QList>
#include<QPixmap>
#include<QRectF>
#include<QPaintEvent>
#include "health.h"
//How to play notes
//key up and then right or left while pressing up (jump)
//space and then right or left while pressing space (hop)
enum movement {StillRight,StillLeft, WalkRight, WalkLeft, JumpRight,JumpLeft, HopRight, HopLeft};
class player: public QObject, public QGraphicsPixmapItem{
public:
    Q_OBJECT
private:
    //bool carringSword;
    score Score;
    health Health;
    movement statue;
    int groundy; //to save the ground info when he climbs it
    int isJumping;
    bool isFalling;
    int isHopping;
    int frame;
    bool isClimb;
    bool stopwalkingRight;
    bool stopwalkingLeft;
    QPixmap currentImageRight;
    QPixmap currentImageLeft;
    QTimer* timer;
    QList<QList<QPixmap>>animationFrames; //0->walkright, 1->walkleft,2->hopRight,3->hopLeft,4->jumpright,5->jumpleft
public:
    player(QGraphicsItem *parent=0,bool right=true);
    void addTextToScreen();
    void setGround();
    QRectF playerBox;
    void checkCollisions();
    void handleRightCollision();
    void handleLeftCollision();
    void handleTopCollision();
    void handleBottomCollision();
    void fall();
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void update();
    void keyPressEvent(QKeyEvent* event); //to control the player using keywords.
    void keyReleaseEvent(QKeyEvent* event);
    //void detectNeighbors();

};
#endif // PLAYER_H
