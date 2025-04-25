#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include "animation.h"

class Enemy : public QObject
{
    Q_OBJECT

public:
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
    void setPosition(const QPoint& pos);

    // Position Management
    QPoint position() const { return m_position; }

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

signals:
    void positionChanged();
    void visualChanged();
    void stateChanged(Enemy::State state);
    void died();

private slots:
    void handleAnimationCompleted(const QString& stateName);

private:
    // Helper to conver enum to string
    QString stateToString(State state) const;

    Animation *m_animation;
    QPoint m_position;
    int m_moveSpeed;
    int m_facingDirection;
};

#endif // ENEMY_H
