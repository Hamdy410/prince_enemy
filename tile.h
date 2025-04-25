#ifndef TILE_H
#define TILE_H
#include<QPainter>
#include<QRectF>
#include<QGraphicsPixmapItem>
class tile: public QGraphicsPixmapItem
{
    QRectF boundingrect;
public:
    int groundy;
    tile(int x, int y); //place;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // TILE_H
