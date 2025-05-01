#ifndef SPIKES_H
#define SPIKES_H
#include "obstacle.h"
#include "player.h"
#include<QTimer>
#include<QGraphicsPixmapItem>
class player;
class Health;
class QPainter;
class Spikes : public Obstacle
{
    Q_OBJECT
public:
    enum State{
        Hidden = 0,
        Level1out= 1,
        Level2out= 2,
        Fullyout= 3
    };
    Q_ENUM(State)
    Spikes(const QPointF& pos);
    ~Spikes() override;
    void Update(player* player) override;
    void onCollide(player* player) override;
    void Activate() override;

    void checkPlayerDistance(player* player);
    void setActivationDistance(float distance);
    void loadSpriteSheet();
    void changeState(State newstate);
    void render(QPainter* painter);
    static constexpr int FRAME_WIDTH= 63;
    static constexpr int FRAME_HEIGHT= 74;

    QRectF hitRegion() const { return m_hitRegion.translated(pos()); }
    void setHitRegion(qreal left, qreal top, qreal right, qreal bottom);

    // Individual direction setters
    void setHitRegionUp(qreal value);
    void setHitRegionDown(qreal value);
    void setHitRegionLeft(qreal value);
    void setHitRegionRight(qreal value);

    // Sink Offset for better interface
    static constexpr int SPIKE_SINK_OFFSET_Y = 45;
private slots:
    void advanceAnimation();

private:

    State m_currentstate;
    QTimer m_animationtimer;
    double m_activationDistance;
    bool m_playerIsThere;

    QPixmap m_spritesheet;

    // Impelemented for better hitting player
    QRectF m_hitRegion;
    qreal m_hitUp, m_hitDown, m_hitLeft, m_hitRight;
};

#endif // SPIKES_H
