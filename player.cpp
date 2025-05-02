#include "player.h"
#include "tile.h"
#include "health.h"
#include "score.h"
#include "pressuretile.h"

#include <QTransform>
#include <QPainter>
#include <QPixmap>
#include <QList>
#include <QDebug>

player::player(bool right, QObject* parent)
    : QObject(parent),
    m_health(3),
    statue(right ? StillRight : StillLeft),
    m_x(100), m_y(100), groundy(100),
    frame(0), isClimb(false),
    isHopping(0), isJumping(0),
    stopwalkingRight(false), stopwalkingLeft(false),
    m_healthBar(new Health(m_health)), m_scoreBar(new Score)
{
    QPixmap SpriteSheet(":/images/Prince_Spritesheet.png");
    double width = SpriteSheet.width() / 14.0;
    double height = SpriteSheet.height() / 38.0;

    // Standing frames
    currentImageRight = SpriteSheet.copy(0, 0, width, height);
    QTransform transform;
    transform.scale(-1, 1);
    currentImageLeft = currentImageRight.transformed(transform);

    // Walk right/left
    QList<QPixmap> walkright, walkleft;
    int x = 0;
    for (int i = 0; i < 14; ++i) {
        QPixmap f = SpriteSheet.copy(x, height, width, height);
        walkright << f;
        walkleft << f.transformed(transform);
        x += width;
    }
    animationFrames << walkright << walkleft;

    // Hop right/left
    QList<QPixmap> hopright, hopleft;
    x = 0;
    for (int i = 0; i < 14; ++i) {
        QPixmap f = SpriteSheet.copy(x, 7 * height, width, height);
        hopright << f;
        hopleft << f.transformed(transform);
        x += width;
    }
    animationFrames << hopright << hopleft;

    // Jump right/left
    QList<QPixmap> jumpright, jumpleft;
    x = 0;
    for (int i = 0; i < 13; ++i) {
        QPixmap f = SpriteSheet.copy(x, 15 * height, width, height);
        jumpright << f;
        jumpleft << f.transformed(transform);
        x += width;
    }
    animationFrames << jumpright << jumpleft;

    QList<QPixmap> armRight, armLeft;
    x = 0;
    for (int i = 0; i < 5; i++) {
        QPixmap f = SpriteSheet.copy(x, 4 * height, width, height);
        armRight << f;
        armLeft << f.transformed(transform);
        x += width;
    }
    animationFrames << armRight << armLeft;

    QList<QPixmap> attackRight, attackLeft;
    x = 0;
    for (int i = 0; i < 8; i++) {
        QPixmap f = SpriteSheet.copy(x, 5 * height, width, height);
        attackRight << f;
        attackLeft << f.transformed(transform);
        x += width;
    }
    animationFrames << attackRight << attackLeft;

    QList<QPixmap> unarmRight, unarmLeft;
    x = 0;
    for (int i = 0; i < 9; i++) {
        QPixmap f = SpriteSheet.copy(x, 3 * height, width, height);
        unarmRight << f;
        unarmLeft << f.transformed(transform);
        x += width;
    }
    animationFrames << unarmRight << unarmLeft;

    qDebug() << "Animation Frames size:" << animationFrames.size();
    for (int i = 0; i < animationFrames.size(); i++)
        qDebug() << "animationFrames[" << i << "].size():" << animationFrames[i].size();

    groundy = m_y;
}

player::~player() {
    delete m_healthBar;
    delete m_scoreBar;
}

void player::handleKeyPress(QKeyEvent* event) {
    if (isClimb) {
        if (event->key() == Qt::Key_Up) {
            statue = (statue == HangLeft) ? ClimbLeft : ClimbRight;
            climbFrame = 0;
            isClimb = false;
        } else if (event->key() == Qt::Key_Down) {
            statue = (statue == HangLeft) ? JumpLeft : JumpRight;
            m_inAir = true;
            isClimb = false;
        }
        return;
    }

    if ((swordOut || armingInProgress || attackInProgress || unarmingInProgress) &&
        !(event->key() == Qt::Key_L || event->key() == Qt::Key_A))
    {
        return;
    }

    if (event->key() == Qt::Key_Right) {
        rightPressed = true;
        if (isHopping == 2 || isJumping == 2) return;
        if (isHopping == 1 && isJumping != 1) {
            isHopping = 2; frame = 0; statue = HopRight;
        } else if (isJumping == 1 && isHopping != 1) {
            isJumping = 2; frame = 0; statue = JumpRight;
        } else if (isHopping == 0 && isJumping == 0) {
            statue = WalkRight;
        }
    } else if (event->key() == Qt::Key_Left) {
        leftPressed = true;
        if (isHopping == 2 || isJumping == 2) return;
        if (isHopping == 1 && isJumping != 1) {
            isHopping = 2; frame = 0; statue = HopLeft;
        } else if (isJumping == 1 && isHopping != 1) {
            isJumping = 2; frame = 0; statue = JumpLeft;
        } else if (isHopping == 0 && isJumping == 0) {
            statue = WalkLeft;
        }
    } else if (event->key() == Qt::Key_Space) {
        if (isHopping != 2 && isJumping != 2) {
            isHopping = 1; isJumping = 0;
        }
    } else if (event->key() == Qt::Key_Up) {
        upPressed = true;
        if (!m_inAir) {
            m_velocityY = -12.0f;
            m_inAir = true;
            statue = (statue == WalkLeft || statue == StillLeft) ? JumpLeft : JumpRight;
            frame = 0;
            m_animCounter = 0;
            jumpBufferFrames = 0;
        }
    } else if (event->key() == Qt::Key_R) {
        if (!swordOut && !armingInProgress && !attackInProgress && !unarmingInProgress) {
            statue = (statue == StillLeft || statue == WalkLeft) ? ArmLeft : ArmRight;
            frame = 0;
            armingInProgress = true;
        }
    } else if (event->key() == Qt::Key_L) {
        if (swordOut && !armingInProgress && !attackInProgress && !unarmingInProgress) {
            statue = (statue == StillLeft || statue == WalkLeft || statue == SwordIdleLeft) ? UnarmLeft : UnarmRight;
            frame = 0;
            unarmingInProgress = true;
        }
    } else if (event->key() == Qt::Key_A) {
        if (swordOut && !attackInProgress && !armingInProgress && !unarmingInProgress) {
            statue = (statue == StillLeft || statue == SwordIdleLeft) ? AttackLeft : AttackRight;
            frame = 0;
            attackInProgress = true;
            m_enemiesHitThisAttack.clear();
        }
    }
}

void player::handleKeyRelease(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right) {
        rightPressed = false;
        if (isHopping != 2 && isJumping != 2)
            statue = StillRight;
    } else if (event->key() == Qt::Key_Left) {
        leftPressed = false;
        if (isHopping != 2 && isJumping != 2)
            statue = StillLeft;
    } else if (event->key() == Qt::Key_Space) {
        if (isHopping != 2 && isJumping != 2) {
            isHopping = 0; isJumping = 0; frame = 0;
        }
    } else if (event->key() == Qt::Key_Up) {
        upPressed = false;
        if (isHopping != 2 && isJumping != 2) {
            isHopping = 0; isJumping = 0; frame = 0;
        }
    }
}

void player::update(const QList<tile*>& tiles) {
    if (jumpBufferFrames > 0) jumpBufferFrames--;

    switch (statue) {
    case WalkRight:
        if (!stopwalkingRight) {
            m_x += 3;
            m_animCounter++;
            if (m_animCounter >= m_animDelay) {
                frame++;
                if (frame >= animationFrames[0].size()) frame = 0;
                m_animCounter = 0;
            }
        }
        break;
    case WalkLeft:
        if (!stopwalkingLeft) {
            m_x -= 3;
            m_animCounter++;
            if (m_animCounter >= m_animDelay) {
                frame++;
                if (frame >= animationFrames[1].size()) frame = 0;
                m_animCounter = 0;
            }
        }
        break;
    case StillRight:
        frame = 0;
        break;
    case StillLeft:
        frame = 0;
        break;
    case HopRight:
        if (isHopping == 1) {
            m_inAir = true;
            isHopping = 2;
            frame = 0;
        }
        m_animCounter++;
        if (m_animCounter >= 4) {
            if (frame < 7) {
                m_x += 10;
                ++frame;
            } else if (frame < 14) {
                m_x += 10;
                ++frame;
            } else {
                statue = StillRight;
                isHopping = 0;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case HopLeft:
        if (isHopping == 1) {
            m_inAir = true;
            isHopping = 2;
            frame = 0;
        }
        m_animCounter++;
        if (m_animCounter >= 4) {
            if (frame < 7) {
                m_x -= 10;
                ++frame;
            } else if (frame < 14) {
                m_x -= 10;
                ++frame;
            } else {
                statue = StillLeft;
                isHopping = 0;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case JumpRight:
    case JumpLeft:
        m_animCounter++;
        if (m_animCounter >= 2) {
            frame++;
            if (statue == JumpRight && frame >= animationFrames[4].size()) frame = 0;
            if (statue == JumpLeft && frame >= animationFrames[5].size()) frame = 0;
            m_animCounter = 0;
        }
        break;
    case ClimbRight:
    case ClimbLeft:
        // TODO: Play climb animation, then move player on top of tile and set Still state
        break;
    case HangRight:
    case HangLeft:
        // TODO: Play hang animation, freeze movement
        break;
    case ArmRight:
    case ArmLeft:
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[6 + (statue == ArmLeft ? 1 : 0)].size()) {
                swordOut = true;
                armingInProgress = false;
                statue = (statue == ArmLeft) ? SwordIdleLeft : SwordIdleRight;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case AttackRight:
    case AttackLeft:
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[8 + (statue == AttackLeft ? 1 : 0)].size()) {
                attackInProgress = false;
                m_enemiesHitThisAttack.clear();
                statue = (statue == AttackLeft) ? SwordIdleLeft : SwordIdleRight;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case UnarmRight:
    case UnarmLeft:
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[10 + (statue == UnarmLeft ? 1 : 0)].size()) {
                swordOut = false;
                unarmingInProgress = false;
                statue = (statue == UnarmLeft) ? StillLeft : StillRight;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case SwordIdleRight:
    case SwordIdleLeft:
        frame = 0;
        break;
    }

    // ---- AIR CONTROL BLOCK ----
    // Allow air control (move left/right in air) when not hopping
    if (m_inAir && statue != HopRight && statue != HopLeft) {
        if (rightPressed && !stopwalkingRight) {
            m_x += 3; // or a lower value for less air control
        }
        if (leftPressed && !stopwalkingLeft) {
            m_x -= 3;
        }
    }
    // ---- END AIR CONTROL BLOCK ----

    // Apply gravity if in air
    if (m_inAir && statue != HopRight && statue != HopLeft) {
        m_y += m_velocityY;
        m_velocityY += 1.0f; // gravity
    }

    // Always check collisions after movement/gravity
    checkCollisions(tiles);

    if (m_justLanded && jumpBufferFrames > 0) {
        m_velocityY = -12.0f; // or your jump velocity
        m_inAir = true;
        statue = (statue == WalkLeft || statue == StillLeft) ? JumpLeft : JumpRight;
        frame = 0;
        m_animCounter = 0;
        jumpBufferFrames = 0; // Consume the buffer
    }


    if (!m_inAir && (statue == JumpRight || statue == JumpLeft)) {
        if (rightPressed && !stopwalkingRight)
            statue = WalkRight;
        else if (leftPressed && !stopwalkingLeft)
            statue = WalkLeft;
        else
            statue = (statue == JumpRight) ? StillRight : StillLeft;

        frame = 0;
    }

    // If landed, reset velocity and air state
    if (!m_inAir) {
        m_velocityY = 0.0f;
    }
}


void player::draw(QPainter* painter) {
    QPixmap framePixmap;
    switch (statue) {
    case WalkRight:
        framePixmap = animationFrames[0][frame % animationFrames[0].size()];
        break;
    case WalkLeft:
        framePixmap = animationFrames[1][frame % animationFrames[1].size()];
        break;
    case HopRight:
        framePixmap = animationFrames[2][qMin(frame, animationFrames[2].size() - 1)];
        break;
    case HopLeft:
        framePixmap = animationFrames[3][qMin(frame, animationFrames[3].size() - 1)];
        break;
    case JumpRight:
        framePixmap = animationFrames[4][qMin(frame, animationFrames[4].size() - 1)];
        break;
    case JumpLeft:
        framePixmap = animationFrames[5][qMin(frame, animationFrames[5].size() - 1)];
        break;
    case StillRight:
        framePixmap = currentImageRight;
        break;
    case StillLeft:
        framePixmap = currentImageLeft;
        break;
    case ArmRight:
        framePixmap = animationFrames[6][qMin(frame, animationFrames[6].size() - 1)];
        break;
    case ArmLeft:
        framePixmap = animationFrames[7][qMin(frame, animationFrames[7].size() - 1)];
        break;
    case AttackRight:
        framePixmap = animationFrames[8][qMin(frame, animationFrames[8].size() - 1)];
        break;
    case AttackLeft:
        framePixmap = animationFrames[9][qMin(frame, animationFrames[9].size() - 1)];
        break;
    case UnarmRight:
        framePixmap = animationFrames[10][qMin(frame, animationFrames[10].size() - 1)];
        break;
    case UnarmLeft:
        framePixmap = animationFrames[11][qMin(frame, animationFrames[11].size() - 1)];
        break;
    case SwordIdleRight:
        framePixmap = animationFrames[6][animationFrames[6].size() - 1];
        break;
    case SwordIdleLeft:
        framePixmap = animationFrames[7][animationFrames[7].size() - 1];
        break;
    default:
        framePixmap = currentImageRight;
        break;
    }

    painter->drawPixmap(QPointF(m_x, m_y + sinkOffset), framePixmap);

    // Debug: Draw bounding box and foot region
    // QRectF box = boundingRect();
    // painter->setPen(Qt::red);
    // painter->drawRect(box.translated(m_x, m_y));

    // QRectF footRegion(
    //     m_x + 3,
    //     m_y + boundingRect().height(),
    //     boundingRect().width() - 6,
    //     2);
    // painter->setBrush(QColor(255, 0, 0, 100));
    // painter->drawRect(footRegion);

    // QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);
    // qreal centerX = playerBox.left() + playerBox.width() / 2.0;
    // qreal hurtX = centerX - HURT_REGION_WIDTH / 2.0;
    // QRectF hurtRegion(hurtX, playerBox.top(), HURT_REGION_WIDTH, playerBox.height());

    // painter->save();
    // painter->setPen(QPen(Qt::magenta, 2));
    // painter->setBrush(QColor(255, 0, 255, 90));
    // painter->drawRect(hurtRegion);
    // painter->restore();

    // QRectF hit = hitRegion();
    // if (!hit.isNull()) {
    //     painter->save();
    //     painter->setPen(QPen(Qt::green, 2));
    //     painter->setBrush(QColor(0, 255, 0, 80));
    //     painter->drawRect(hit);
    //     painter->restore();
    // }

    QRectF feet = feetRegion();
    if (!feet.isNull()) {
        painter->save();
        painter->setPen(QPen(Qt::magenta, 1 , Qt::DashLine));
        painter->drawRect(feet);
        painter->restore();
    }
}

QRectF player::boundingRect() const {
    QPixmap framePixmap = currentImageRight;
    if (!animationFrames.isEmpty() && !animationFrames[0].isEmpty())
        framePixmap = animationFrames[0][0];
    return QRectF(0, 0, framePixmap.width(), framePixmap.height());
}

QPointF player::pos() const {
    return QPointF(m_x, m_y);
}

void player::setPos(qreal x, qreal y) {
    m_x = x;
    m_y = y;
}

void player::setGround(qreal groundY) {
    groundy = groundY;
}

void player::checkCollisions(const QList<tile*> &tiles) {
    m_justLanded = false;
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);

    // 1. Check for landing on top of a tile
    for (tile* t: tiles) {
        QRectF tileBox = t->boundingRect().translated(t->pos().x(), t->pos().y());
        float overlapLeft = playerBox.right() - tileBox.left();
        float overlapRight = tileBox.right() - playerBox.left();
        float overlapTop = playerBox.bottom() - tileBox.top();
        float overlapBottom = tileBox.bottom() - playerBox.top();
        float minOverlap = qMin(qMin(overlapLeft, overlapRight), qMin(overlapTop, overlapBottom));

        if (playerBox.intersects(tileBox)) {
            if (minOverlap == overlapTop && m_inAir && m_velocityY >= 0) {
                // Landed from above
                m_y = t->pos().y() - playerBox.height();
                groundy = m_y;
                m_inAir = false;
                m_velocityY = 0.0f;
                m_justLanded = true;

                // --- FALL DAMAGE LOGIC ---
                float fallDistance = m_y - m_fallStartY;
                const float FALL_DAMAGE_THRESHOLD = 100.0f;

                if (fallDistance > FALL_DAMAGE_THRESHOLD) {
                    takeDamage(1);
                    qDebug() << "Fall Damage! Distance:" << fallDistance;
                }

                PressureTile *pt = dynamic_cast<PressureTile*>(t);
                if (pt && feetRegion().intersects(tileBox)) {
                    pt->setPressed(!pt->isPressed());
                }

                break;
            }
            // TODO: Add ledge grab and side collision logic here if desired
        }
    }

    // 2. If not landed, check if feet are supported
    if (!m_justLanded) {
        QRectF footRegion(
            m_x + 3,
            m_y + boundingRect().height() - sinkOffset,
            boundingRect().width() - 6,
            2
            );
        bool supported = false;
        for (const tile* t : tiles) {
            QRectF tileBox = t->boundingRect().translated(t->pos().x(), t->pos().y());
            if (tileBox.intersects(footRegion)) {
                supported = true;
                break;
            }
        }
        // If not supported and not already in air or jumping/hopping, start falling
        if (!supported && !m_inAir) {
            m_inAir = true;
            m_velocityY = 0.0f;
            m_fallStartY = m_y; // Record the starting Y position for fall damage
        }
    }
}

void player::takeDamage(int amount) {
    m_health -= amount;
    if (m_health < 0) m_health = 0;
    m_healthBar->decrease(amount);
    qDebug() << "Player hit! Health is now:" << m_health;
}

QRectF player::hurtRegion() const {
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);
    qreal centerX = playerBox.left() + playerBox.width() / 2.0;
    qreal hurtX = centerX - HURT_REGION_WIDTH / 2.0;
    return QRectF(hurtX, playerBox.top(), HURT_REGION_WIDTH, playerBox.height());
}

QRectF player::hitRegion() const {
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);
    int swordLength = 40;
    if (statue == AttackRight || statue == SwordIdleRight) {
        return QRectF(playerBox.right(), playerBox.top() + playerBox.height() * 0.2, swordLength, playerBox.height() * 0.6);
    } else if (statue == AttackLeft || statue == SwordIdleLeft) {
        return QRectF(playerBox.left() - swordLength, playerBox.top() + playerBox.height() * 0.2,
                      swordLength, playerBox.height() * 0.6);
    }

    return QRectF();
}

QRectF player::feetRegion() const {
    QRectF box = boundingRect();
    const qreal feetHeight = 9;
    const qreal widthFraction = 0.2;
    const qreal feetWidth = box.width() * widthFraction;

    const qreal xOffset = m_x + (box.width() - feetWidth) / 2;

    const qreal yOffset = m_y + box.height() - feetHeight + 4;

    return QRectF(
        xOffset,
        yOffset,
        feetWidth,
        feetHeight);
}
