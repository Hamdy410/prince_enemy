#ifndef GATE_H
#define GATE_H

#include <QGraphicsPixmapItem>

class Gate : public QGraphicsPixmapItem
{
public:
    Gate(const QPointF& pos);

    bool isSolid() const { return true; } // Always solid for now

    static constexpr int SINK_OFFSET = 40;

private:
    void loadImage();
};

#endif // GATE_H
