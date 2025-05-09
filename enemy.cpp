#include "enemy.h"

#include <QPainter>
#include <QDebug>
#include <QTransform>

Enemy::Enemy(QObject* parent)
    : QObject(parent)
    , m_animation(new Animation(this))
    , m_moveSpeed(1)
    , m_currentState(WALKRIGHT)
    , m_alive(true)
    , m_facingDirection(1)  // Add a dedicated direction variable (1=right, -1=left)
    , m_isAttacking(false)
    , m_attackCooldown(2000)
    , m_currentCooldown(0)
    , m_player(nullptr)
    , m_isPatrolling(true)
{
    connect(m_animation, &Animation::frameChanged, this, [this](int) {
        emit visualChanged();
    });

    connect(m_animation, &Animation::stateChanged, this, [this](const QString&) {
        emit visualChanged();
    });

    connect(m_animation, &Animation::animationCompleted, this, &Enemy::handleAnimationCompleted);
}

Enemy::~Enemy() {
    // Animation is deleted automatically through parent-child relationship
}

bool Enemy::initialize(const QString& spritesheet, int frameWidth, int frameHeight) {
    // Load the spritesheet
    if (!m_animation->loadSpritesheet(spritesheet, frameWidth, frameHeight)) {
        return false;
    }

    // Use the same rows for all animations - we'll handle flipping in render()
    m_animation->addState("walk_right", 0, 7, true, true, 0);     // Direction is ignored
    m_animation->addState("attack_right", 1, 4, false, false, 0);
    m_animation->addState("die_right", 2, 5, false, false, 0);
    m_animation->addState("walk_left", 0, 7, true, true, 0);      // Direction is ignored
    m_animation->addState("attack_left", 1, 4, false, false, 0);
    m_animation->addState("die_left", 2, 5, false, false, 0);

    // Start with walking right
    setState(WALKRIGHT);
    m_animation->start(15);

    return true;
}

QString Enemy::stateToString(State state) const {
    switch(state) {
    case WALKRIGHT: return "walk_right";
    case ATTACKRIGHT: return "attack_right";
    case DIERIGHT: return "die_right";
    case WALKLEFT: return "walk_left";
    case ATTACKLEFT: return "attack_left";
    case DIELEFT: return "die_left";
    default: return "unknown";
    }
}

bool Enemy::setState(State state) {
    // If already in this state, no change needed
    if (m_currentState == state) {
        return true;
    }

    // Rule 1: If the enemy is dead, only allow resurrection by external code
    if (!m_alive && state != DIERIGHT && state != DIELEFT) {
        return false;
    }

    // Rule 2: Allow movement states to interrupt attack animations
    bool isAttackState = (m_currentState == ATTACKRIGHT || m_currentState == ATTACKLEFT);
    bool isMovementRequest = (state == WALKRIGHT || state == WALKLEFT);

    // Determine if state transition is allowed
    bool canTransition = !isAttackState || isMovementRequest;

    if (canTransition) {
        QString stateName = stateToString(state);

        // Set the state in the animation
        bool success = m_animation->setState(stateName);

        if (success) {
            // Update our internal state
            m_currentState = state;

            // Update facing direction based on the new state
            if (state == WALKRIGHT || state == ATTACKRIGHT || state == DIERIGHT) {
                m_facingDirection = 1;  // Right
            } else {
                m_facingDirection = -1; // Left
            }

            // Handle animation based on state type
            if (state == ATTACKRIGHT || state == ATTACKLEFT) {
                // Always restart attack animations
                m_animation->stop();
                m_animation->start(m_animation->desiredFrameRate());
            }
            else if ((state == WALKRIGHT || state == WALKLEFT) && !m_animation->isRunning()) {
                // Ensure walking animations are running
                m_animation->start(m_animation->desiredFrameRate());
            }
            else if (state == DIERIGHT || state == DIELEFT) {
                // Mark as dead for death animations
                m_alive = false;
                m_animation->stop();
                m_animation->start(m_animation->desiredFrameRate());
            }

            emit stateChanged(state);
            return true;
        }
    }

    return false;
}

void Enemy::setPosition(const QPointF &pos) {
    if (pos.x() != m_position.x() || pos.y() != m_position.y()) {
        m_position = pos;
        setPos(pos);
        emit positionChanged();
    }
}

void Enemy::update(int windowWidth) {
    updateCooldown();

    if (checkPlayerCollision() && m_currentCooldown == 0) {
        attackPlayer();
        return;
    }

    // Only move the enemy if in a movable state (walking) and animation is running
    if (m_animation->isRunning() && (m_currentState == WALKRIGHT || m_currentState == WALKLEFT)) {
        if (m_isPatrolling && checkForEdge()) {
            m_facingDirection *= -1;
            setState(m_facingDirection > 0 ? WALKRIGHT : WALKLEFT);
            return;
        }

        QPointF pos = m_position;

        // Use the facing direction to determine movement
        pos.setX(pos.x() + m_facingDirection * m_moveSpeed);

        // Screen wrapping logic
        if (pos.x() > windowWidth && m_facingDirection > 0) {
            pos.setX(-m_animation->frameWidth());
        } else if (pos.x() < -m_animation->frameWidth() && m_facingDirection < 0) {
            pos.setX(windowWidth);
        }

        setPosition(pos);
    }
}

void Enemy::render(QPainter *painter) {
    QPixmap frame = m_animation->currentFrame();
    if (!frame.isNull()) {
        // Check if we need to flip the image horizontally (for left-facing states)
        bool shouldFlip = (m_facingDirection < 0);  // Flip whenever facing left

        if (shouldFlip) {
            // Save the current painter state
            painter->save();

            // Set up transformation for horizontal flipping
            painter->translate(m_position.x() + frame.width(), m_position.y());
            painter->scale(-1, 1);

            // Draw the flipped frame at the origin (0,0) since we've translated
            painter->drawPixmap(QPointF(0, 0), frame);

            // Restore the painter state
            painter->restore();
        } else {
            // Draw normally for right-facing states
            painter->drawPixmap(m_position, frame);
        }

        // // Draw debug information (bounding box and state text)
        //  painter->setPen(Qt::red);
        //  painter->drawRect(QRectF(m_position, QSizeF(frame.width(), frame.height())));

        // // State and direction indicator
        // QString direction = (m_facingDirection < 0) ? "◄" : "►";
        // QString stateInfo = QString("%1 %2 (Frame %3/%4)")
        //                          .arg(stateToString(m_currentState))
        //                         .arg(direction)
        //                         .arg(m_animation->currentFrameIndex() + 1)
        //                         .arg(m_animation->isLooping() ? "∞" :
        //                                  QString::number(m_animation->frameCount()));

        //  painter->setPen(Qt::black);
        //  painter->drawText(m_position.x(), m_position.y() - 5, stateInfo);

        // // Draw cooldown indicator (for debugging)
        //  if (m_currentCooldown > 0) {
        //     int cooldownPercentage = (m_currentCooldown * 100) / m_attackCooldown;
        //     int barWidth = m_animation->frameWidth();
        //     int filledWidth = (barWidth * (100 - cooldownPercentage)) / 100;
        //     painter->fillRect(m_position.x(), m_position.y() - 10, barWidth, 5, Qt::red);
        //     painter->fillRect(m_position.x(), m_position.y() - 10, filledWidth, 5, Qt::green);
        // }

        // QRectF enemyRect(m_position, QSizeF(m_animation->frameWidth(), m_animation->frameHeight()));
        // Determine the hit region

        // QRectF hitRegion = enemyRect;
        // if (m_facingDirection > 0) {
        //     hitRegion.setLeft(hitRegion.left() + hitRegion.width() / 2.0);
        // } else {
        //     hitRegion.setWidth(hitRegion.width() / 2.0);
        // }

        // painter->save();
        // painter->setPen(QPen(Qt::blue, 2));
        // painter->setBrush(QColor(0, 0, 255, 100));
        // painter->drawRect(hitRegion);
        // painter->restore();

        // QRectF hurt = hurtRegion();
        // painter->save();
        // painter->setPen(QPen(Qt::red, 2));
        // painter->setBrush(QColor(255, 0, 0, 80));
        // painter->drawRect(hurt);
        // painter->restore();
    }
}

void Enemy::setAnimationSpeed(int fps) {
    m_animation->setFrameRate(fps);
}

int Enemy::animationSpeed() const {
    return m_animation->isRunning() ?
               1000 / m_animation->m_timer.interval() :
               m_animation->desiredFrameRate();
}

void Enemy::handleAnimationCompleted(const QString& stateName) {
    // Only process completion events for the current state
    if ((stateName == "die_right" && m_currentState == DIERIGHT) ||
        (stateName == "die_left" && m_currentState == DIELEFT)) {
        // Death animation completed
        emit died();
        // Keep showing the last frame of death animation
    }
    else if ((stateName == "attack_right" && m_currentState == ATTACKRIGHT) ||
             (stateName == "attack_left" && m_currentState == ATTACKLEFT)) {
        // Attack animation completed - transition back to appropriate walking state
        m_isAttacking = false;
        State nextState = (m_facingDirection > 0) ? WALKRIGHT : WALKLEFT;

        // Set the next state
        setState(nextState);

        // Ensure animation is running
        if (!m_animation->isRunning()) {
            m_animation->start(m_animation->desiredFrameRate());
        }
    }
}

void Enemy::forceCompleteCurrentAnimation() {
    QString stateName = stateToString(m_currentState);
    handleAnimationCompleted(stateName);
}

bool Enemy::checkPlayerCollision() {
    if (!m_player || !m_alive || m_isAttacking)
        return false;

    QRectF enemyRect(m_position, QSize(m_animation->frameWidth(), m_animation->frameHeight()));
    QRectF playerRect = m_player->boundingRect().translated(m_player->pos());

    // --- Define the "front half" hit region ---
    QRectF hitRegion = enemyRect;
    if (m_facingDirection > 0) {
        // Facing right: right half
        hitRegion.setLeft(hitRegion.left() + hitRegion.width() / 2.0);
    } else {
        // Facing left: left half
        hitRegion.setWidth(hitRegion.width() / 2.0);
    }

    return hitRegion.intersects(m_player->hurtRegion());
}

void Enemy::attackPlayer() {
    if (m_isAttacking || m_currentCooldown > 0 || !m_alive)
        return;

    if (m_facingDirection > 0) {
        setState(ATTACKRIGHT);
    } else {
        setState(ATTACKLEFT);
    }

    m_isAttacking = true;
    m_currentCooldown = m_attackCooldown;

    // --- Damage the player here ---
    if (m_player) {
        m_player->takeDamage(1);
    }
}

void Enemy::updateCooldown() {
    if (m_currentCooldown > 0) {
        m_currentCooldown -= 16;

        if (m_currentCooldown < 0)
            m_currentCooldown = 0;
    }
}

bool Enemy::checkForEdge() {
    if (m_tiles.isEmpty())
        return false;

    // calculate the position where we need to check for ground
    // We check slightly ahead of the enemy in the direction it's facing
    int checkX = pos().x() + (m_facingDirection > 0 ? boundingRect().width() + 5 : -5);
    int checkY = pos().y() + boundingRect().height() + 5 - ENEMY_TILE_OVERLAP; // check slightly below the feet

    // Check if there's ground at this position
    QPointF checkPoint(checkX, checkY);
    bool foundGround = false;

    for (QGraphicsItem* item : m_tiles) {
        QRectF tileRect = item->boundingRect();

        if (checkX >= tileRect.left() && checkX <= tileRect.right()) {
            if (qAbs(checkY - tileRect.top()) < 10) {
                foundGround = true;
                break;
            }
        }
    }

    return !foundGround;
}

void Enemy::takeDamage(int amount) {
    m_health -= amount;
    if (m_health <= 0) {
        m_health = 0;
        m_alive = false;
        setState(m_facingDirection > 0 ? DIERIGHT : DIELEFT);
        emit died();
    }

}

QRectF Enemy::hurtRegion() const {
    QRectF enemyBox(m_position, QSizeF(m_animation->frameWidth(), m_animation->frameHeight()));
    qreal centerX = enemyBox.left() + enemyBox.width() / 2.0;
    qreal hurtX = centerX - HURT_REGION_WIDTH / 2.0;
    return QRectF(hurtX, enemyBox.top(), HURT_REGION_WIDTH, enemyBox.height());
}
