/*
 * Author: Kareem Adel
 * Start Date:
 * End Date:
 */

#ifndef SCORE_H
#define SCORE_H
#include<QGraphicsTextItem>
class score: public QGraphicsTextItem{
public:
    score(QGraphicsItem* parent=0);
    int value;
    void getdecrease();
    void getincrease();
};


#endif // SCORE_H
