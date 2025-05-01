#include "spikes.h"
#include"obstacle.h"
#include"player.h"
#include <QPainter>
#include <QGraphicsScene>
#include<QLineF>
#include "health.h"

Spikes::Spikes(const QPointF& pos)
    : Obstacle(pos, false, false, false),
    m_currentstate(Hidden),
    m_activationDistance(10000.0),  // Changed detection distance for now.
    m_playerIsThere(false)
{
    m_animationtimer.setInterval(700);
    connect(&m_animationtimer, &QTimer::timeout, this, &Spikes::advanceAnimation);
    loadSpriteSheet();
    setPos(pos);
    qDebug() << "Spikes created at" << pos << "with activation distance" << m_activationDistance;

    setHitRegion(25, 25, 25, 30);
}


void Spikes::loadSpriteSheet()
{ QPixmap spriteSheet(":/images/spikes.png");
    if (spriteSheet.isNull()) {
        qWarning("Failed to load spikes sprite sheet");
        return;
    }
    m_spritesheet = spriteSheet;

    changeState(Hidden);
}


void Spikes::changeState(State newstate)
{

    if(m_currentstate == newstate)
        return;
    if(m_spritesheet.isNull()){
        qWarning("sprite not loaded");
        return;
    }
    m_currentstate =  newstate;
    int frameX = static_cast<int>(m_currentstate) * FRAME_WIDTH;

    if(frameX + FRAME_WIDTH > m_spritesheet.width())
    {
        qWarning("Frame out of spritesheet bounds");
        return;
    }
    QPixmap frame= m_spritesheet.copy(frameX, 0, FRAME_WIDTH,FRAME_HEIGHT);
    if(!frame.isNull()){
        setPixmap(frame);
    }
    switch(m_currentstate)
    {
    case Hidden:
        qDebug() << "Spike is now hidden";
        setVisible(true);
        m_solid = false;
        m_damaging= false;
        break;
    case Level1out:
    case Level2out:
        setVisible(true);
        m_solid = false;
        m_damaging= false;
        break;
    case Fullyout:
        qDebug() << "Spike is now fully extended";
        setVisible(true);
        m_solid = true;
        m_damaging= true;
        break;
    }

}


void Spikes::advanceAnimation()
{
    if (m_spritesheet.isNull())
        return;

    switch(m_currentstate)
    {
    case Hidden:
        changeState(Level1out);

        break;
    case Level1out:
        changeState(Level2out);

        break;


    case Level2out:
        changeState(Fullyout);

        break;

    case Fullyout:
        m_animationtimer.stop();
        break;

    }

}
void Spikes::setActivationDistance(float distance)
{
    m_activationDistance = distance;
}



void Spikes::onCollide(player* player)
{
    if(!player || m_currentstate != Fullyout)
        return;

    if (player->hurtRegion().intersects(hitRegion())) {
        qWarning("The player is killed");
        player->takeDamage(100);
    }
}


void Spikes::checkPlayerDistance(player* player)
{

    qreal distance = QLineF(pos(), player->pos()).length();
    if(distance <= m_activationDistance){
        m_playerIsThere= true;
        Activate();
    }
    else
    {
        m_playerIsThere= false;
    }
}


void Spikes::Activate()  {
    if (m_currentstate == Hidden && !m_animationtimer.isActive()) {

        m_animationtimer.start();

    }
}

void Spikes::Update(player* player)
{
    if(!player)
        return;

    checkPlayerDistance(player);
}

Spikes::~Spikes()  {
    m_animationtimer.stop();
    disconnect(&m_animationtimer, nullptr, this, nullptr);
}
void Spikes::render(QPainter *painter){
    painter->drawPixmap(pos(), pixmap());

    // Draw Bounding rect in red for debugging
    // painter->setPen(QPen(Qt::red, 1));
    // painter->drawRect(boundingRect().translated(pos()));

    // // // Draw hit region in blue
    // painter->setPen(QPen(Qt::blue, 2));
    // painter->setBrush(QBrush(QColor(0, 0, 255, 50)));
    // painter->drawRect(hitRegion());
}


void Spikes::setHitRegion(qreal left, qreal top, qreal right, qreal bottom) {
    m_hitUp = top; m_hitDown = bottom; m_hitLeft = left; m_hitRight = right;

    qreal centerX = FRAME_WIDTH / 2.0;
    qreal centerY = FRAME_HEIGHT / 2.0;
    m_hitRegion = QRectF(centerX - m_hitLeft,
                         centerY - m_hitUp,
                         m_hitLeft + m_hitRight,
                         m_hitUp = m_hitDown);
}
