#ifndef PRESSURETILE_H
#define PRESSURETILE_H

#include "tile.h"

class PressureTile : public tile
{
public:
    PressureTile(int x, int y, bool hasEnemy = false);

    bool isPressed() const { return m_pressed; }
    void setPressed(bool pressed);

    int normalY() const { return m_normalY; }
    int pressedY() const { return m_pressedY; }

    QRectF activationRegion() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    bool m_pressed;
    int m_normalY;
    int m_pressedY;
};

#endif // PRESSURETILE_H
