#ifndef ANIMATION_H
#define ANIMATION_H
#include<QList>
#include<QPixmap>
#include<QMap>
#include<QPointF>
//complete guide for using animation
//first create an animation object and the parameters are the link of the SpriteSheet, numberofRows, numberOfColumns.
//if you want to add an animatoin state, you have two ways (by the row or by the upperleft). addAnimation Function
//remember if you want the animation to start, call start() function
// the frame change and the setPixmap happens manually. call the function nextFrame() in a timer and this function returns an image.
//important functions: constructor, addAnimation(), nextFrame(), start(), stop(), and if you want the frame, the variable is public.
class Animation{
    int availableIndex;
    double defaultWidth;
    double defaultHeight;
    QPixmap SpriteSheet;
    int counter;
    int frame;
    int delay;
    QTransform transform;
    int indexOfCurrentAnimation;
    QList<QList<QPixmap>>sourceImages;
    QMap<QString,int>indexIdentifiers;
public:
    bool playing;
    int getFrame(){return frame;}
    int AnimationSize();
    void setDelay(int d){delay=d; counter=0;}
    Animation(QString Url, int numberOfRows=1,int numberOfColumns=1);
    void stop(){frame=0;}
    void start(QString name);
    void addAnimation(QString name, int number_of_row, int numberOfFrames,bool reverse,int width=-1, int height=-1);
    void addAnimation(QString name, int start_x,int start_y, int numberOfFrames,bool reverse,int width=-1, int height=-1);
    QPixmap nextFrame();
    QPixmap currentFrame();
};
#endif
