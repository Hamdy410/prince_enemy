#include "player.h"
#include<QGraphicsTextItem>
#include<QGraphicsItem>
#include<QObject>
#include<QGraphicsPixmapItem>
#include<QList>
#include<QPixmap>
#include<QTransform>
#include<QPainter>
#include<QKeyEvent>
#include<QGraphicsScene>
#include<QTimer>
#include "tile.h"
player::player(QGraphicsItem* parent,bool right):QGraphicsPixmapItem(parent),Score(parent),Health(parent) {
    Score.setPos(0,0);
    Health.setPos(0,20);
    isClimb=false;
    isFalling=false;
    frame=0;
    isHopping=0;
    stopwalkingLeft=false;
    stopwalkingRight=false;
    isJumping=0;
    QPixmap SpriteSheet(":/images/Prince_Spritesheet.png");
    double width = SpriteSheet.rect().width()/14;
    double height = SpriteSheet.rect().height()/38;
    QPixmap frame = SpriteSheet.copy(0,0,width,height);
    currentImageRight = frame;
    QTransform transform;
    transform = transform.scale(-1,1);
    frame = frame.transformed(transform);
    currentImageLeft = frame;
    if(right){
        setPixmap(currentImageRight);
        statue = StillRight;
    }else{
        setPixmap(currentImageLeft);
        statue = StillLeft;
    }
    QList<QPixmap>walkright;
    QList<QPixmap>walkleft;
    int x=0;
    for(int i=0;i<14;i++){
        frame = SpriteSheet.copy(x,height,width,height);
        walkright<<frame;
        frame = frame.transformed(transform);
        walkleft<<frame;
        x+= width;
    }
    animationFrames<<walkright;
    animationFrames<<walkleft;
    QList<QPixmap>hopright;
    QList<QPixmap>hopleft;
    x=0;
    for(int i=0;i<14;i++){
        frame = SpriteSheet.copy(x,7*height,width,height);
        hopright<<frame;
        frame = frame.transformed(transform);
        hopleft<<frame;
        x+= width;
    }
    animationFrames<<hopright;
    animationFrames<<hopleft;
    QList<QPixmap>jumpright;
    QList<QPixmap>jumpleft;
    x=0;
    for(int i=0;i<13;i++){
        frame = SpriteSheet.copy(x,15*height,width,height);
        jumpright<<frame;
        frame = frame.transformed(transform);
        jumpleft<<frame;
        x+= width;
    }
    animationFrames<<jumpright;
    animationFrames<<jumpleft;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(50);
}
/*
void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Draw your player sprite/image first (if any)
    painter->drawPixmap(0, 0, pixmap());
    playerBox = QRect(0.2*boundingRect().width(),0.3*boundingRect().height(),0.6*boundingRect().width(),0.7*boundingRect().height());
    // Draw the bounding rect with color
    painter->setPen(QPen(Qt::red, 2));      // Red outline, 2px thick
    painter->setBrush(Qt::transparent);     // Transparent fill
    painter->drawRect(playerBox);      // Draw the bounding rectangle
}
*/
void player::keyPressEvent(QKeyEvent* event){
    if(event->key()==Qt::Key_Right){
        if(isHopping==2 || isJumping==2){
            return ;
        }
        if(isHopping==1 && isJumping!=1){
            isHopping=2;
            frame=0;
            statue=HopRight;
        }else if(isJumping==1 && isHopping!=1){
            isJumping=2;
            frame=0;
            statue=JumpRight;
        }else if(isHopping==0 && isJumping==0){
            statue = WalkRight;
        }
    }else if(event->key()==Qt::Key_Left){
        if(isHopping==2 || isJumping==2){
            return ;
        }
        if(isHopping==1 && isJumping!=1){
            isHopping=2;
            frame=0;
            statue=HopLeft;
        }else if(isJumping==1 && isHopping!=1){
            isJumping=2;
            frame=0;
            statue=JumpLeft;
        }else if(isHopping==0 && isJumping==0){
            statue = WalkLeft;
        }
    }else if(event->key()==Qt::Key_Space){
        if(isHopping!=2 && isJumping!=2){
            isHopping=1;
            isJumping=0;
        }
    }else if(event->key()==Qt::Key_Up){
        if(isJumping!=2 && isHopping!=2){
            isJumping=1;
            isHopping=0;
        }

    }
}
void player::addTextToScreen(){
    scene()->addItem(&Score);
    scene()->addItem(&Health);
}
void player::setGround(){
    playerBox = boundingRect();
    groundy=y();
}
void player::keyReleaseEvent(QKeyEvent* event){
    if(event->key()==Qt::Key_Right){
        if(isHopping!=2 && isJumping!=2)
            statue = StillRight;
    }else if(event->key()==Qt::Key_Left){
        if(isHopping!=2 && isJumping!=2)
            statue= StillLeft;
    }else if(event->key()==Qt::Key_Space){
        if(isHopping!=2 && isJumping!=2){
            isHopping=0;
            isJumping=0;
            frame=0;
            if(statue==StillRight){
                statue=StillRight;
            }
            if(statue==StillLeft){
                statue=StillLeft;
            }
        }
    }else if(event->key()==Qt::Key_Up){
        if(isHopping!=2 && isJumping!=2){
            isHopping=0;
            isJumping=0;
            frame=0;
            if(statue==StillRight){
                statue=StillRight;
            }
            if(statue==StillLeft){
                statue=StillLeft;
            }
        }
    }
}
void player::update(){
    if(statue==WalkRight && !stopwalkingRight){
        setPos(x()+5,groundy);
        if(frame>=animationFrames[0].size()){
            frame=0;
        }
        setPixmap(animationFrames[0][frame++%14]);
    }else if(statue==WalkLeft && !stopwalkingLeft){
        setPos(x()-5,groundy);
        if(frame>=animationFrames[1].size()){
            frame=0;
        }
        setPixmap(animationFrames[1][frame++%14]);
    }else if(statue==StillRight){
        setPixmap(currentImageRight);
    }else if(statue==StillLeft){
        setPixmap(currentImageLeft);
    }else if(statue==HopRight){
        if(frame<7){
            setPos(x()+10,y()-5);
            setPixmap(animationFrames[2][frame++]);
        }else if(frame<14){
            setPos(x()+10,y()+5);
            setPixmap(animationFrames[2][frame++]);
        }else{
            setPos(x(),groundy);
            statue = StillRight;
            isHopping=0;
            frame=0;
        }

    }else if(statue==HopLeft){
        if(frame<7){
            setPos(x()-10,y()-5);
            setPixmap(animationFrames[3][frame++]);
        }else if(frame<14){
            setPos(x()-10,y()+5);
            setPixmap(animationFrames[3][frame++]);
        }else{
            setPos(x(),groundy);
            statue = StillLeft;
            isHopping=0;
            frame=0;
        }
    }else if(statue==JumpRight){
        if(frame<10){
            setPos(x(),y()-10);
            setPixmap(animationFrames[4][frame++]);
        }else if(frame<13){
            if(!isClimb)
                setPos(x(),y()+20);
            setPixmap(animationFrames[4][frame++]);
        }else{
            setPos(x(),groundy);
            statue = StillRight;
            isJumping=false;
            frame=0;
        }
    }else if(statue==JumpLeft){
        if(frame<10){
            setPos(x(),y()-10);
            setPixmap(animationFrames[5][frame++]);
        }else if(frame<13){
            if(!isClimb)
                setPos(x(),y()+20);
            setPixmap(animationFrames[5][frame++]);
        }else{
            setPos(x(),groundy);
            statue = StillLeft;
            isJumping=false;
            frame=0;
        }
    }
    if(isFalling)
        fall();
    checkCollisions();
}
void player:: fall(){
    if(!isFalling)
        return ;
    if(statue==JumpRight || statue==JumpLeft || statue==HopLeft || statue==HopRight){
        return ;
    }
    if(y()>scene()->height() -boundingRect().height() - 60){
        groundy = scene()->height() -boundingRect().height() - 60;
        isFalling=false;
        return ;
    }
    setPos(x(),y()+10);
    groundy+=10;
    checkCollisions();
}
void player::checkCollisions(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(auto& neighbor: colliding_items){
        tile* obj = dynamic_cast<tile*>(neighbor);
        if(obj){
            QRectF otherBox = neighbor->mapRectToItem(this, neighbor->boundingRect());
            float overlapLeft = playerBox.right() - otherBox.left();
            float overlapRight = otherBox.right() - playerBox.left();
            float overlapTop = playerBox.bottom() - otherBox.top();
            float overlapBottom = otherBox.bottom() - playerBox.top();
            float minOverlap = qMin(qMin(overlapLeft, overlapRight), qMin(overlapTop, overlapBottom));
            if (minOverlap == overlapTop) {
                //handleTopCollision();
                qDebug()<<"top"<<Qt::endl;
                isFalling=false;
                groundy = obj->groundy - 0.9 * boundingRect().height();
                stopwalkingRight=false;
                stopwalkingLeft=false;
            } else if(minOverlap == overlapBottom){
                if(statue==JumpRight){
                    if(overlapRight>=overlapLeft){
                        isClimb=true;
                        isFalling=false;
                        groundy = obj->groundy - 0.9 * boundingRect().height();
                        stopwalkingRight=false;
                        stopwalkingLeft=false;
                        return ;

                    }
                }else if(statue==JumpLeft){
                    if(overlapRight<=overlapLeft){
                        isClimb=true;
                        isFalling=false;
                        groundy = obj->groundy - 0.9 * boundingRect().height();
                        stopwalkingRight=false;
                        stopwalkingLeft=false;
                        return ;
                    }
                }
                isFalling=false;
            }else if(minOverlap==overlapRight){
                stopwalkingRight=true;
            }else{
                stopwalkingLeft=true;
            }
            return ;
        }
    }
    stopwalkingRight=false;
    stopwalkingLeft=false;
    qDebug()<<"pre-fall"<<Qt::endl;
    if(statue!=JumpRight && statue!=JumpLeft){
        isFalling=true;
        qDebug()<<"fall"<<Qt::endl;
    }
}

