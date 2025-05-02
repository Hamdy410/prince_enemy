#include "gate.h"
#include <QDebug>

Gate::Gate(const QPointF& pos) : QGraphicsPixmapItem(nullptr)
{
    // Load the gate image
    loadImage();

    // Set position
    setPos(pos);

    qDebug() << "Gate created at position:" << pos;
}

void Gate::loadImage()
{
    // Try to load the gate image
    QPixmap gateImage(":/images/gate.png");

    if (gateImage.isNull()) {
        qWarning() << "Gate: Failed to load image from :/images/gate.png";

        // Fallback - create a simple colored rectangle as placeholder
        QPixmap fallback(40, 80);
        fallback.fill(Qt::red);
        setPixmap(fallback);
    } else {
        // If we have multiple frames, just use the first one for now
        int frameWidth = gateImage.width() / 16; // Assuming 16 frames
        QPixmap firstFrame = gateImage.copy(0, 0, frameWidth, gateImage.height());
        setPixmap(firstFrame);

        qDebug() << "Gate: Image loaded successfully, size:" << firstFrame.size();
    }
}
