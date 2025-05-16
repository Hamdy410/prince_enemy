#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPixmap>
#include <QRectF>
#include <QKeyEvent>
#include <QList>
#include <QSet>
#include "player_animation.h"
#include "score.h"
#include "health.h"
#include "gate.h"
class tile;
class Enemy;

enum movement {
    StillRight, StillLeft, WalkRight, WalkLeft,
    JumpRight, JumpLeft, HopRight, HopLeft, AttackLeft,
    AttackRight,crouchRight,crouchLeft
};

class player : public QObject {
    Q_OBJECT

public:
    player(bool right = true, QObject* parent = nullptr);
    ~player();
    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);
    void update(const QList<tile*>& tiles, const QList<Gate*>& gates);
    void draw(QPainter* painter);
    QRectF boundingRect();
    QPointF pos() const;
    void setPos(qreal x, qreal y);
    // int Score() const { return m_score.value; }
    // int Health() const { return m_health.value; }
    void setGround(qreal groundY);

    // Animation Movement dynamics
    static constexpr int sinkOffset = 6;

    // Attack methods
    void takeDamage(int amount);
    QRectF hurtRegion();
    bool isCrouching;
    QRectF hitRegion();
    QRectF feetRegion();
    bool isAttacking(){ return is_attacking; }
    QSet<Enemy*>& enemiesHitThisAttack() { return m_enemiesHitThisAttack; }

    // Health and Score representations:
    Health* healthBar() const { return m_healthBar; }
    Score* scoreBar() const { return m_scoreBar; }
    bool isDead() const { return m_health <= 0; }

private:
    void checkCollisions(const QList<tile*>& tiles, const QList<Gate*>& gates);

    // score m_score;
    // health m_health;

    int m_health = 100;
    Animation* player_anim;
    movement statue;
    qreal m_x, m_y;
    qreal groundy;
    int frame;
    int isHopping;
    bool RightFacingDirection;
    int isJumping;
    bool isFalling;
    QPixmap currentImageRight;
    QPixmap currentImageLeft;
    QList<QList<QPixmap>> animationFrames;
    void fall(const QList<tile*>& tiles, const QList<Gate*>& gates);
    // Animation helpers
    int m_animCounter = 0;
    int m_animDelay = 8;
    // Attack Animation Parameters
    bool is_attacking = false;
    static constexpr int HURT_REGION_WIDTH = 27;
    QSet<Enemy*> m_enemiesHitThisAttack;

    // Health and Score Handling
    Health* m_healthBar;
    Score* m_scoreBar;

    // Fall Damage system
    float falling_distance = 0.0f;
    float damage_of_falling=0;

    //jump simultaneously
    bool upPressed = false;
    const int JUMP_BUFFER_MAX = 4;
};

#endif
