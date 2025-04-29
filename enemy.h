/*
 * Author: Hamdy El-Madbouly
 * Start Date: 17 April, 2025
 * End Date:
 * Description:
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
