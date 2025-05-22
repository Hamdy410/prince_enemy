/*
 * The Chopper class represents a timed obstacle that changes its state over time.
 *
 * It cycles through three states: Closed, PartialOpen, and Open. Each state lasts a configurable
 * amount of time. When a player collides with it while it's in a dangerous state (e.g., Closed or
 * Partial open) it caause damage)
 */

#ifndef CHOPPER_H
#define CHOPPER_H

#include "obstacle.h"
#include <QTimer>

class Chopper : public Obstacle {
    Q_OBJECT

public:
    // States representing the chopper's current phase
    enum State { Closed, PartialOpen, Open };

    Chopper(const QPointF& pos,
            int damage = 1,
            int closedDelay = 400,
            int partialOpenDelay = 400,
            int openDelay = 2000);

    // Handles player collision depending on the current state.
    void onCollide(player* player) override;

    // Returns the current state.
    State getState() const { return m_state; }
    void render(QPainter *painter);

    // Returns true if the chopper is in the Open (safe) state.
    bool complete(){return m_state==Open;}

private slots:
    void advanceState();

private:
    // Updates appearance based on the current state.
    void updateAppearance();

    State m_state;
    int m_damage;
    QTimer m_timer;
    int m_closedDelay;
    int m_partialOpenDelay;
    int m_openDelay;
};

#endif // CHOPPER_H
