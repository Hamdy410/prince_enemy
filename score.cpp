#include "score.h"
#include<QFont>
score::score(QGraphicsItem* parent):QGraphicsTextItem(parent) {
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
    value=0;
    setPlainText("Score: "+QString::number(value));
}
void score::getdecrease(){
    value--;
    setPlainText("Score: "+QString::number(value));
}
void score::getincrease(){
    value++;
    setPlainText("Score: "+QString::number(value));
}
