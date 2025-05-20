#include "player_animation.h".h"
#include<QList>
#include<QPixmap>
#include<QMap>
#include<QDebug>
#include<QPointF>
Animation::Animation(QString Url, int numberOfRows, int numberOfColumns){
    frame=0;
    delay=0;
    counter=0;
    this->defaultHeight = defaultHeight;
    this->defaultWidth = defaultWidth;
    playing=false;
    availableIndex=0;
    indexOfCurrentAnimation=-1;
    SpriteSheet = QPixmap(Url);
    transform = transform.scale(-1,1);
    defaultWidth = SpriteSheet.rect().width()/numberOfRows;
    defaultHeight = SpriteSheet.rect().height()/numberOfColumns;
}
void Animation::addAnimation(QString name, int start_x,int start_y, int numberOfFrames, bool reverse,int width, int height){
    if(width==-1 || height==-1){
        width = defaultWidth;
        height= defaultHeight;
    }
    indexIdentifiers[name]=availableIndex++;
    QList<QPixmap>animationFrames;
    QPixmap framepic;
    for(int i=0;i<numberOfFrames;i++){
        framepic = SpriteSheet.copy(start_x,start_y,width,height);
        if(reverse)
            framepic = framepic.transformed(transform);
        animationFrames<<framepic;
        start_x+= width;
    }
    sourceImages<<animationFrames;
}
void Animation::addAnimation(QString name, int number_of_row, int numberOfFrames, bool reverse,int width, int height){
    if(width==-1 || height==-1){
        width = defaultWidth;
        height= defaultHeight;
    }
    indexIdentifiers[name]=availableIndex++;
    QList<QPixmap>animationFrames;
    QPixmap framepic;
    int start_y = (number_of_row-1)*defaultHeight;
    int start_x = 0;
    for(int i=0;i<numberOfFrames;i++){
        framepic = SpriteSheet.copy(start_x,start_y,width,height);
        if(reverse)
            framepic = framepic.transformed(transform);
        animationFrames<<framepic;
        start_x+= width;
    }
    sourceImages<<animationFrames;
}
void Animation::start(QString name){
    if(!(indexIdentifiers.contains(name))){
        qDebug()<<"no animation state with that name"<<Qt::endl;
        return ;
    }
    indexOfCurrentAnimation = indexIdentifiers[name];
}

QPixmap Animation::nextFrame(){
    if(frame>=sourceImages[indexOfCurrentAnimation].size()){
        frame=0;
    }
    counter++;
    if(counter<delay)
        return sourceImages[indexOfCurrentAnimation][frame];
    else{
    counter=0;
    return sourceImages[indexOfCurrentAnimation][frame++];
    }
}
QPixmap Animation::currentFrame(){
    if(frame>=sourceImages[indexOfCurrentAnimation].size()){
        frame=0;
    }
    return sourceImages[indexOfCurrentAnimation][frame];
}
int Animation::AnimationSize(){
    return sourceImages[indexOfCurrentAnimation].size();
}
