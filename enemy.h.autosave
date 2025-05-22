/*
 * Author: Hamdy El-Madbouly
 * Start Date: 17 April, 2025
 * End Date:   20 April, 2025
 * Description: Enemy Characters
 * 
 * This class implements an animated enemy character with state-based behavior.
 * The Enemy class handles its own movement, animation, collision detection and
 * interaction wit the player and environment.
 * 
 * States include: walking, attacking, and dying with appropriate animations for
 * each state.
 * 
 * Features:
 *      - Patrol Behavior with edge detction to prevent falling
 *      - Attack system with cooldown management
 *      - Automatic sprite flipping based on movement direction
 *      
 * Usage:
 *      1. Create an Enemy instance
 *      2. Initialize with a spritesheet containing animation frames.
 *      3. Set position, movement speed, and other properties
 *      4. Connect to signals for state changes and death events.
 *      5. Call update() in your game loop to handle movement and state changes
 *      6. Call render() to draw the enemy or use as a QGraphicsItem
 *      
 * Animation Requirements:
 *      - Row 0: Walking animation (7 frames)
 *      - Row 1: Attack animation (4 frames)
 *      - Row 2: Death animation (5 frames)
 *      
 * State Transitions:
 *      - Walking states can be interrupted by any other state
 *      - Attack states can only be interrupted by movements states
 *      - Death states cannot be interrupted (enemy remains dead)
 *      
 * Collision System:
 *      - Hit Region: Area in front of the enemy that can damage the player
 *      - Hurt Region: Area where the enemy can be damaged by the player
 *      - Tile detection: Used for edge detection during patrol b
 * 
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QGraphicsItem>
#include <QPainter>
#include <QList>

#include "animation.h"
#include "player.h"

class Enemy : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    static constexpr int ENEMY_TILE_OVERLAP = 5;

    enum State {
        WALKRIGHT,
        ATTACKRIGHT,
        DIERIGHT,
        WALKLEFT,
        ATTACKLEFT,
        DIELEFT
    };
    Q_ENUM(State)

    explicit Enemy(QObject* parent = nullptr);
    ~Enemy();

    // setup
    bool initialize(const QString& spritesheet, int frameWidth, int frameHeight);

    // State Management
    bool setState(State state);
    void setPosition(const QPointF& pos);

    // Position Management
    QPointF position() const { return m_position; }

    // Speed Control
    void setMoveSpeed(int speed) { m_moveSpeed = speed; }
    int moveSpeed() const { return m_moveSpeed; }

    // Update and render
    void update(int windowWidth);
    void render(QPainter *paitner);

    // Animation speed control
    void setAnimationSpeed(int fps);
    int animationSpeed() const;

    // Status
    bool isAlive() const { return m_alive; }

    bool m_alive;
    State m_currentState;

    void forceCompleteCurrentAnimation();

    void setPlayer(player* p) { m_player = p; }
    bool checkPlayerCollision();
    void attackPlayer();
    void updateCooldown();

    void setTiles(const QList<QGraphicsItem*>& tiles) { m_tiles = tiles; }
    void startPatrolling() { m_isPatrolling = true; }
    void stopPatrolling() { m_isPatrolling = false; }

    QRectF boundingRect() const override {
        return QRectF(0, 0, m_animation->frameWidth(), m_animation->frameHeight());
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget = nullptr) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        QPixmap frame = m_animation->currentFrame();
        if (!frame.isNull()) {
            painter->drawPixmap(0, 0, frame);
        }
    }

    void takeDamage(int amount);
    QRectF hurtRegion() const;
    int health() const { return m_health; }

    void resetAnimation() {
        m_animation->stop();
        m_animation->start(15);
    }

    QRectF calculateHitRegion() const;

signals:
    void positionChanged();
    void visualChanged();
    void stateChanged(Enemy::State state);
    void died();

private slots:
    void handleAnimationCompleted(const QString& stateName);

private:
    // Helper to convert enum to string
    QString stateToString(State state) const;

    Animation *m_animation;
    QPointF m_position;
    double m_moveSpeed;
    int m_facingDirection;

    // Player collision handling
    bool m_isAttacking;
    int m_attackCooldown;
    int m_currentCooldown;
    player* m_player;

    // Tile collision and interaction
    QList<QGraphicsItem*> m_tiles;
    bool m_isPatrolling;
    bool checkForEdge();

    // Health dynamics
    int m_health = 3;
    static constexpr int HURT_REGION_WIDTH = 30;
};

#endif // ENEMY_H
