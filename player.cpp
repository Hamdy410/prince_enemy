#include "player.h"
#include "tile.h"

#include <QTransform>
#include <QPainter>
#include <QPixmap>
#include <QList>
#include <QDebug>

player::player(bool right, QObject* parent)
    : QObject(parent),
    m_score(),
    m_health(),
    statue(right ? StillRight : StillLeft),
    m_x(100), m_y(100), groundy(100),
    frame(0), isClimb(false),
    isHopping(0), isJumping(0),
    stopwalkingRight(false), stopwalkingLeft(false)
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

    groundy = m_y;
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

    if (event->key() == Qt::Key_Right) {
        if (isHopping == 2 || isJumping == 2) return;
        if (isHopping == 1 && isJumping != 1) {
            isHopping = 2; frame = 0; statue = HopRight;
        } else if (isJumping == 1 && isHopping != 1) {
            isJumping = 2; frame = 0; statue = JumpRight;
        } else if (isHopping == 0 && isJumping == 0) {
            statue = WalkRight;
        }
    } else if (event->key() == Qt::Key_Left) {
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
        if (!m_inAir) {
            m_velocityY = -12.0f;
            m_inAir = true;
            statue = (statue == WalkLeft || statue == StillLeft) ? JumpLeft : JumpRight;
            frame = 0;
            m_animCounter = 0;
        }
    }
}

void player::handleKeyRelease(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right) {
        if (isHopping != 2 && isJumping != 2)
            statue = StillRight;
    } else if (event->key() == Qt::Key_Left) {
        if (isHopping != 2 && isJumping != 2)
            statue = StillLeft;
    } else if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Up) {
        if (isHopping != 2 && isJumping != 2) {
            isHopping = 0; isJumping = 0; frame = 0;
        }
    }
}

void player::update(const QList<tile*>& tiles) {
    switch (statue) {
    case WalkRight:
        if (!stopwalkingRight) {
            m_x += 5;
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
            m_x -= 5;
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
    }

    // Apply gravity if in air
    if (m_inAir) {
        m_y += m_velocityY;
        m_velocityY += 1.0f; // gravity
    }

    // Always check collisions after movement/gravity
    checkCollisions(tiles);

    if (!m_inAir && (statue == JumpRight || statue == JumpLeft)) {
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
    default:
        framePixmap = currentImageRight;
        break;
    }

    painter->drawPixmap(QPointF(m_x, m_y + sinkOffset), framePixmap);

    // Debug: Draw bounding box and foot region
    // QRectF box = boundingRect();
    // painter->setPen(Qt::red);
    // painter->drawRect(box.translated(m_x, m_y));

    QRectF footRegion(
        m_x + 3,
        m_y + boundingRect().height(),
        boundingRect().width() - 6,
        2);
    // painter->setBrush(QColor(255, 0, 0, 100));
    // painter->drawRect(footRegion);
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

void player::checkCollisions(const QList<tile *> &tiles) {
    m_justLanded = false;
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);

    // 1. Check for landing on top of a tile
    for (const tile* t: tiles) {
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
        }
    }
}
