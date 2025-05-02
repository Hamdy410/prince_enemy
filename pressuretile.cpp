#include "pressuretile.h"
#include "gate.h"

PressureTile::PressureTile(int x, int y, bool hasEnemy)
    : tile(x, y - 2, hasEnemy),
    m_pressed(false),
    m_normalY(y - 2),
    m_pressedY(y),
    m_connectedGate(nullptr)
{
    setPos(x, m_normalY);
}

void PressureTile::setPressed(bool pressed) {
    if (m_pressed == pressed)
        return;

    m_pressed = pressed;
    setPos(pos().x(), pressed ? m_pressedY : m_normalY);

    if (m_connectedGate) {
        if (pressed) {
            m_connectedGate->Open();
        } else {
            m_connectedGate->Close();
        }
    }
}

QRectF PressureTile::activationRegion() const {
    QRectF tileBox = boundingRect();

    const qreal regionHeight = 4;
    const qreal widthFraction = 0.6;
    const qreal regionWidth = tileBox.width() * widthFraction;

    return QRectF(
        (tileBox.width() - regionWidth) / 2,
        0,
        regionWidth,
        regionHeight
        );
}

void PressureTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // First draw the pixmap (parent implementation)
    tile::paint(painter, option, widget);

    // Draw the activation region (for debugging)
    QRectF region = activationRegion();

    painter->setPen(QPen(Qt::cyan, 2, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(region);

    // Also draw a border around the whole tile
    painter->setPen(QPen(isPressed() ? Qt::red : Qt::blue, 2));
    painter->drawRect(boundingRect());
}

