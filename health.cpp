#include "health.h"
#include<QFont>
health::health(QGraphicsItem* parent):QGraphicsTextItem(parent) {
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
    value=100;
    setPlainText("Health: "+QString::number(value));
}
void health::getdecrease(){
    value--;
    setPlainText("Health: "+QString::number(value));
}
void health::getincrease(){
    value++;
    setPlainText("Health: "+QString::number(value));
}
