#ifndef HEALTH_H
#define HEALTH_H
#include<QGraphicsTextItem>
class health: public QGraphicsTextItem{
public:
    health(QGraphicsItem* parent=0);
    int value;
    void getdecrease();
    void getincrease();
};


#endif // HEALTH_H
