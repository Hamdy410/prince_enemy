#ifndef TILE_H
#define TILE_H

#include<QPainter>
#include<QRectF>
#include<QGraphicsPixmapItem>

class tile: public QGraphicsPixmapItem
{
public:
    int groundy;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    tile(int x, int y, bool hasEnemy);
    bool hasEnemy() const { return m_hasEnemy; }
    void setHasEnemy(bool value) { m_hasEnemy = value; }

private:
    QRectF boundingrect;
    bool m_hasEnemy;
};

#endif // TILE_H
