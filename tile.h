/*
 * Original Author: Kareem Adel
 * Modified by: Hamdy El-Madbouly
 * Start Date:
 * Modification Date: 25 Dec, 2025
 * End Date: 26 Dec, 2025
 * Description:
 */

#ifndef TILE_H
#define TILE_H

#include<QPainter>
#include<QRectF>
#include<QGraphicsRectItem>

class tile: public QGraphicsRectItem
{
public:
    int groundy;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    tile(int x, int y, bool hasEnemy);
    bool hasEnemy() const { return m_hasEnemy; }
    void setHasEnemy(bool value) { m_hasEnemy = value; }

private:
    QRectF boundingrect;
    bool m_hasEnemy;
};

#endif // TILE_H
