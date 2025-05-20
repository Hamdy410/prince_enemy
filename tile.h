#ifndef TILE_H
#define TILE_H

#include<QRectF>
#include"structure.h"

class tile: public Structure
{
public:
    int groundy;
    tile(int x, int y, int width, int height, QString label, bool hasEnemy);
    bool hasEnemy() const { return m_hasEnemy; }
    void setHasEnemy(bool value) { m_hasEnemy = value; }

private:
    QRectF boundingrect;
    bool m_hasEnemy;
};

#endif // TILE_H
