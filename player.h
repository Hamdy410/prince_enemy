/*
 * Original Author: Kareem Adel
 * Modified and re-implemented by: Hamdy El-Madbouly
 * Start Date:
 * Modification Date: 26 Dec, 2025
 * End Date:
 * Description:
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QRectF>
#include <QTimer>
#include <QKeyEvent>
#include <QList>

#include "score.h"
#include "health.h"

class tile;

enum movement {StillRight, StillLeft, WalkRight, WalkLeft, JumpRight,
                JumpLeft, HopRight, HopLeft, ClimbRight, ClimbLeft, HangRight,
                HangLeft};

class player : public QObject {
    Q_OBJECT

public:
    player(bool right = true, QObject* parent=nullptr);
    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);
    void update(const QList<tile*>& tiles);
    void draw(QPainter* painter);
    QRectF boundingRect() const;
    QPointF pos() const;
    void setPos(qreal x, qreal y);
    int Score() const { return m_score.value; }
    int Health() const { return m_health.value; }

    // For collision
    QRectF playerBox;

    // For ground/patform logic
    void setGround(qreal groundY);

    void fall();

    void checkCollisions(const QList<tile*>& tiles);

private:
    score m_score;
    health m_health;
    movement statue;
    qreal m_x, m_y;
    int isJumping;
    bool isFalling;
    int isHopping;
    int frame;
    bool isClimb;
    bool stopwalkingRight;
    bool stopwalkingLeft;
    QPixmap currentImageRight;
    QPixmap currentImageLeft;
    QList<QList<QPixmap>> animationFrames;
    qreal groundy;

    // Handling Animation; and refractorization requirements
    // Author: Hamdy
    int m_animCounter = 0;
    int m_animDelay = 8;
    float m_velocityY = 0.0f;
    bool m_inAir = false;
    int climbFrame = 0;
    int hangFrame = 0;

};

#endif
