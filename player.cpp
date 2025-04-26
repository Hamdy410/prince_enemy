#include "player.h"
#include <QTransform>
#include <QDebug>
#include <QPainter>

player::player(bool right, QObject* parent)
    : QObject(parent),
    m_score(),
    m_health(),
    statue(right ? StillRight : StillLeft),
    m_x(100), // starting x position
    m_y(100), // starting y position
    groundy(100),
    isJumping(0),
    isFalling(false),
    isHopping(0),
    frame(0),
    isClimb(false),
    stopwalkingRight(false),
    stopwalkingLeft(false),
    timer(new QTimer(this))
{
    // Load sprite sheet and prepare animation frames
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
        QPixmap frame = SpriteSheet.copy(x, height, width, height);
        walkright << frame;
        walkleft << frame.transformed(transform);
        x += width;
    }
    animationFrames << walkright << walkleft;

    // Hop right/left
    QList<QPixmap> hopright, hopleft;
    x = 0;
    for (int i = 0; i < 14; ++i) {
        QPixmap frame = SpriteSheet.copy(x, 7 * height, width, height);
        hopright << frame;
        hopleft << frame.transformed(transform);
        x += width;
    }
    animationFrames << hopright << hopleft;

    // Jump right/left
    QList<QPixmap> jumpright, jumpleft;
    x = 0;
    for (int i = 0; i < 13; ++i) {
        QPixmap frame = SpriteSheet.copy(x, 15 * height, width, height);
        jumpright << frame;
        jumpleft << frame.transformed(transform);
        x += width;
    }
    animationFrames << jumpright << jumpleft;

    // Set up the timer for animation and logic updates
    connect(timer, &QTimer::timeout, this, &player::update);
    timer->start(50); // 20 FPS

    groundy = m_y;
}

void player::handleKeyPress(QKeyEvent* event) {
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
        if (isJumping != 2 && isHopping != 2) {
            isJumping = 1; isHopping = 0;
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
            if (statue == StillRight) statue = StillRight;
            if (statue == StillLeft) statue = StillLeft;
        }
    }
}

void player::update() {
    // Animation and movement logic
    switch (statue) {
    case WalkRight:
        if (!stopwalkingRight) {
            m_x += 5;
            if (frame >= animationFrames[0].size()) frame = 0;
            ++frame;
        }
        break;
    case WalkLeft:
        if (!stopwalkingLeft) {
            m_x -= 5;
            if (frame >= animationFrames[1].size()) frame = 0;
            ++frame;
        }
        break;
    case StillRight:
        frame = 0;
        break;
    case StillLeft:
        frame = 0;
        break;
    case HopRight:
        if (frame < 7) {
            m_x += 10; m_y -= 5;
            ++frame;
        } else if (frame < 14) {
            m_x += 10; m_y += 5;
            ++frame;
        } else {
            m_y = groundy;
            statue = StillRight;
            isHopping = 0;
            frame = 0;
        }
        break;
    case HopLeft:
        if (frame < 7) {
            m_x -= 10; m_y -= 5;
            ++frame;
        } else if (frame < 14) {
            m_x -= 10; m_y += 5;
            ++frame;
        } else {
            m_y = groundy;
            statue = StillLeft;
            isHopping = 0;
            frame = 0;
        }
        break;
    case JumpRight:
        if (frame < 10) {
            m_y -= 10;
            ++frame;
        } else if (frame < 13) {
            if (!isClimb) m_y += 20;
            ++frame;
        } else {
            m_y = groundy;
            statue = StillRight;
            isJumping = false;
            frame = 0;
        }
        break;
    case JumpLeft:
        if (frame < 10) {
            m_y -= 10;
            ++frame;
        } else if (frame < 13) {
            if (!isClimb) m_y += 20;
            ++frame;
        } else {
            m_y = groundy;
            statue = StillLeft;
            isJumping = false;
            frame = 0;
        }
        break;
    }

    fall();
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
    }
    painter->drawPixmap(QPointF(m_x, m_y), framePixmap);

    // Draw bounding box (for debugging)
    QRectF box = boundingRect();
    painter->setPen(Qt::red);
    painter->drawRect(box.translated(m_x, m_y));
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

void player::fall() {
    const int gravity = 5;

    if (m_y < groundy) {
        m_y += gravity;
        if (m_y > groundy) {
            m_y = groundy;
        }
        isFalling = true;
    } else {
        m_y = groundy;
        isFalling = false;
    }
}
