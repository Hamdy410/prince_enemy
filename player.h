#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QRectF>
#include <QKeyEvent>
#include <QList>
#include <QSet>

#include "score.h"
#include "health.h"

class tile;
class Enemy;

enum movement {
    StillRight, StillLeft, WalkRight, WalkLeft,
    JumpRight, JumpLeft, HopRight, HopLeft,
    ClimbRight, ClimbLeft, HangRight, HangLeft,
    ArmRight, ArmLeft, UnarmRight, UnarmLeft,
    SwordIdleRight, SwordIdleLeft, AttackLeft,
    AttackRight
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
    // int Health() const { return m_health.value; }
    void setGround(qreal groundY);

    // Animation Movement dynamics
    static constexpr int sinkOffset = 6;

    // Attack methods
    void takeDamage(int amount);
    QRectF hurtRegion() const;
    QRectF hitRegion() const;
    bool isAttacking() const { return attackInProgress; }
    QSet<void*> enemiesHitThisAttack() { return m_enemiesHitThisAttack; }

private:
    void checkCollisions(const QList<tile*>& tiles);

    score m_score;
    // health m_health;

    int m_health = 100;

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
    bool m_justLanded = false;

    // Ledge grab helpers
    int climbFrame = 0;
    int hangFrame = 0;

    // Attack Animation Parameters
    bool swordOut = false;
    bool attackInProgress = false;
    bool armingInProgress = false;
    bool unarmingInProgress = false;
    static constexpr int HURT_REGION_WIDTH = 27;
    QSet<void*> m_enemiesHitThisAttack;
};

#endif
