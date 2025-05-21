// gate.cpp
#include "gate.h"
#include <QDebug>

Gate::Gate(const QPointF& pos) :
    QGraphicsPixmapItem(nullptr),
    m_isOpen(false),
    m_isAnimating(false),
    m_isOpening(false),
    m_currentFrame(0),
    m_totalFrames(0)
{
    loadAnimationFrames();

    if (!m_frames.isEmpty()) {
        setPixmap(m_frames[0]);
    } else {
        QPixmap fallback(40, 80);
        fallback.fill(Qt::red);
        setPixmap(fallback);
    }

    setPos(pos);
    connect(&m_animationTimer, &QTimer::timeout, this, &Gate::updateAnimation);
}

Gate::~Gate()
{
    m_animationTimer.stop();
}

void Gate::loadAnimationFrames()
{
    QPixmap spritesheet(":/images/gate.png");

    if (spritesheet.isNull()) {
        return;
    }

    int columns = 16;
    int frameWidth = spritesheet.width() / columns;
    int frameHeight = spritesheet.height();

    m_totalFrames = columns;
    m_frames.clear();
    for (int i = 0; i < columns; ++i) {
        QPixmap frame = spritesheet.copy(i * frameWidth, 0, frameWidth, frameHeight);
        frame = frame.scaled(frameWidth,frameHeight+30);
        m_frames.push_back(frame);


}
}

void Gate::Open()
{
    if (!m_isOpen && !m_isAnimating) {

        m_isAnimating = true;
        m_isOpening = true;
        m_animationTimer.start(FRAME_DURATION);
    }
}

void Gate::Close()
{
    if (m_isOpen && !m_isAnimating) {

        m_isAnimating = true;
        m_isOpening = false;
        m_animationTimer.start(FRAME_DURATION);
    }
}

void Gate::updateAnimation()
{
    if (m_isOpening) {
        // Opening animation
        m_currentFrame++;
        if (m_currentFrame >= m_totalFrames) {
            m_currentFrame = m_totalFrames - 1;
            m_animationTimer.stop();
            m_isAnimating = false;
            m_isOpen = true;
        }
    } else {
        // Closing animation
        m_currentFrame--;
        if (m_currentFrame <= 0) {
            m_currentFrame = 0;
            m_animationTimer.stop();
            m_isAnimating = false;
            m_isOpen = false;
        }
    }

    // Update the displayed frame
    if (m_currentFrame >= 0 && m_currentFrame < m_frames.size()) {
        setPixmap(m_frames[m_currentFrame]);
    }
}
