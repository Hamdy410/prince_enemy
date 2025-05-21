#ifndef PRESSURETILE_H
#define PRESSURETILE_H

#include "tile.h"
#include <QPixmap>

class Gate;

class PressureTile : public tile
{
public:
    PressureTile(int x, int y, bool hasEnemy = false,int width=60, int height=2);

    bool isPressed() const { return m_pressed; }
    void setPressed(bool pressed);

    int normalY() const { return m_normalY; }
    int pressedY() const { return m_pressedY; }

    void connectToGate(Gate* gate) { m_connectedGate = gate; }
    Gate* connectedGate() const { return m_connectedGate; }
    bool hasConnectedGate() const { return m_connectedGate != nullptr; }

    QRectF activationRegion() const;

    QPixmap *image;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void draw(QPainter* painter);

private:
    bool m_pressed;
    int m_normalY;
    int m_pressedY;
    Gate* m_connectedGate;
};

#endif // PRESSURETILE_H
