#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QRectF>
#include <QKeyEvent>
#include <QList>
#include "score.h"
#include "health.h"

class tile;

enum movement {
    StillRight, StillLeft, WalkRight, WalkLeft,
    JumpRight, JumpLeft, HopRight, HopLeft,
    ClimbRight, ClimbLeft, HangRight, HangLeft
};

class player : public QObject {
    Q_OBJECT

public:
    player(bool right = true, QObject* parent = nullptr);
    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);
    void update(const QList<tile*>& tiles);
    void draw(QPainter* painter);
    QRectF boundingRect() const;
    QPointF pos() const;
    void setPos(qreal x, qreal y);
    int Score() const { return m_score.value; }
    int Health() const { return m_health.value; }
    void setGround(qreal groundY);

private:
    void checkCollisions(const QList<tile*>& tiles);

    score m_score;
    health m_health;
    movement statue;
    qreal m_x, m_y;
    qreal groundy;
    int frame;
    bool isClimb;
    int isHopping;
    int isJumping;
    bool stopwalkingRight;
    bool stopwalkingLeft;
    QPixmap currentImageRight;
    QPixmap currentImageLeft;
    QList<QList<QPixmap>> animationFrames;

    // Animation helpers
    int m_animCounter = 0;
    int m_animDelay = 8;

    // Falling/jumping physics
    float m_velocityY = 0.0f;
    bool m_inAir = false;

    // Ledge grab helpers
    int climbFrame = 0;
    int hangFrame = 0;
};

#endif
