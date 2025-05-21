/*
 * Original Author: Kareem Adel
 * Modified by: Hamdy El-Madbouly
 * Start Date:
 * Modification Date: 25 Dec, 2025
 * End Date: 26 Dec, 2025
 * Description:
 */

#ifndef CEILING_H
#define CEILING_H

#include<QPainter>
#include<QRectF>
#include<QGraphicsRectItem>

class ceiling: public QGraphicsRectItem
{
public:
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    ceiling(int x, int y, int width , int height);

private:
    QRectF boundingrect;
};

#endif // WALL_H
