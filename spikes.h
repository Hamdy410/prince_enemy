/*
  A rising spike trap that animates through multiple danger levels and damages the player on contact.
 */
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
    // Called every frame to update the spike's state
    void Update(player* player) override;

    // Handles player collision logic.
    void onCollide(player* player) override;

    // Triggers activation behavior (e.g., rise-up animation).
    void Activate() override;

    // Returns true if spikes are fully out.
    bool complete(){return m_currentstate==Fullyout;}
    void checkPlayerDistance(player* player);
    // Sets the distance within which spikes activate.
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
