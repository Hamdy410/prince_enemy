#include "choppers.h"
#include "player.h"
#include <QPainter>

Chopper::Chopper(const QPointF& pos, int damage,
                 int closedDelay, int partialOpenDelay, int openDelay)
    : Obstacle(pos, true, true, true),
    m_state(State::Closed),
    m_damage(damage),
    m_closedDelay(closedDelay),
    m_partialOpenDelay(partialOpenDelay),
    m_openDelay(openDelay)
{

    updateAppearance();
    m_timer.setSingleShot(true);
    m_timer.start(m_closedDelay);
    connect(&m_timer, &QTimer::timeout, this, &Chopper::advanceState);
}

void Chopper::advanceState() {
    switch (m_state) {
    case State::Closed:
        m_state = State::PartialOpen;
        m_solid = true;
        m_damaging = true;
        m_timer.start(m_partialOpenDelay);
        break;

    case State::PartialOpen:
        m_state = State::Open;
        m_solid = false;
        m_damaging = false;
        m_timer.start(m_openDelay);
        break;

    case State::Open:
        m_state = State::Closed;
        m_solid = true;
        m_damaging = true;
        m_timer.start(m_closedDelay);
        break;
    }

    updateAppearance();
}

void Chopper::updateAppearance() {
    switch (m_state) {
    case State::Closed:
        setPixmap(QPixmap(":/images/ChopperClosed.jpg"));
        break;
    case State::PartialOpen:
        setPixmap(QPixmap(":/images/ChopperPartialopen.jpg"));
        break;
    case State::Open:
        setPixmap(QPixmap(":/images/ChopperOpen.jpg"));
        break;
    }
}

void Chopper::onCollide(player* player) {
    if (m_state != State::Open) {
        player->takeDamage(m_damage);
    }
}

void Chopper::render(QPainter *painter) {
    painter->drawPixmap(pos(), pixmap());
}
