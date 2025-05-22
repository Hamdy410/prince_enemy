// This class defines the main Player character in the game.
// It handles movement, jumping, crouching, attacking, animation, health, score,
// and interactions with various game elements like tiles, gates, enemies, and obstacles.

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
#include "chopper.h"
#include "wall.h"
#include "ceiling.h"
class tile;
class Enemy;

// Enum for defining different movement states of the player
enum movement {
    StillRight, StillLeft, WalkRight, WalkLeft,
    JumpRight, JumpLeft, HopRight, HopLeft, AttackLeft,
    AttackRight,crouchRight,crouchLeft
};

class player : public QObject {
    Q_OBJECT

public:
     // Constructor and Destructor
    player(bool right = true, int health=15, int score =0,QObject* parent = nullptr);
    ~player();

    // Handle key press and release for controlling player
    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);

    // Update player state including movement and collisions
    void update(const QList<tile*>& tiles, const QList<Gate*>& gates,const QList<Chopper*>& choppers,const QList<wall*>& walls,const QList<ceiling*>& ceilings);

     // Draw the player on the screen
    void draw(QPainter* painter);

    // Get player's bounding rectangle for collision detection
    QRectF boundingRect() const;
    QPointF pos() const;
    void setPos(qreal x, qreal y);

    // Set the Y-coordinate of the ground for jumping/falling logic
    void setGround(qreal groundY);

    // Animation Movement dynamics
    static constexpr int sinkOffset = 6;

    // Attack methods
    void takeDamage(int amount);
    QRectF hurtRegion() const;
    QRectF hitRegion() const;
    QRectF feetRegion() const;
    bool isAttacking(){ return is_attacking; }
    QSet<Enemy*>& enemiesHitThisAttack() { return m_enemiesHitThisAttack; }

    // Health and Score representations:
    Health* healthBar() const { return m_healthBar; }
    Score* scoreBar() const { return m_scoreBar; }
    bool isDead() const { return m_health <= 0; }

private:
    void checkCollisions(const QList<tile*>& tiles, const QList<Gate*>& gates,const QList<Chopper*>& choppers,const QList<wall*>& walls,const QList<ceiling*>& ceilings);

    int m_health = 100;
    Animation* player_anim;
    movement statue;
    qreal m_x, m_y;
    qreal groundy;
    int frame;
    int isHopping;
    bool RightFacingDirection;
    int isJumping;
    bool rightPressed=false;
    bool leftPressed=false;
    bool isFalling;
    QPixmap currentImageRight;
    QPixmap currentImageLeft;
    QList<QList<QPixmap>> animationFrames;
    void fall(const QList<tile*>& tiles, const QList<Gate*>& gates,const QList<Chopper*>& choppers,const QList<wall*>& walls,const QList<ceiling*>& ceilings);
    bool isCrouching;

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
