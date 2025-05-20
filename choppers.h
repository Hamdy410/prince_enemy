#ifndef CHOPPER_H
#define CHOPPER_H

#include "obstacle.h"
#include <QTimer>

class Chopper : public Obstacle {
    Q_OBJECT

public:
    enum State { Closed, PartialOpen, Open };

    Chopper(const QPointF& pos,
            int damage = 1,
            int closedDelay = 400,
            int partialOpenDelay = 400,
            int openDelay = 2000);

    void onCollide(player* player) override;
    State getState() const { return m_state; }
    void render(QPainter *painter);

private slots:
    void advanceState();

private:
    void updateAppearance();

    State m_state;
    int m_damage;
    QTimer m_timer;
    int m_closedDelay;
    int m_partialOpenDelay;
    int m_openDelay;
};

#endif // CHOPPER_H
