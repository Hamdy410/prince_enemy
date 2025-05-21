/*
 * Original Author: Kareem Adel
 * Modified by: Hamdy El-Madbouly
 * Start Date:
 * Modification Date: 25 Dec, 2025
 * End Date: 26 Dec, 2025
 * Description:
 */

#ifndef WALL_H
#define WALL_H

#include<QPainter>
#include<QRectF>
#include<QGraphicsRectItem>

class wall: public QGraphicsRectItem
{
public:
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    wall(int x, int y, int width , int height,bool right);
    bool getRight(){return isRight;}
private:
    QRectF boundingrect;
    bool isRight;
};

#endif // WALL_H
