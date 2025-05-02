#include "animation.h"
#include <QDebug>

Animation::Animation(QObject* parent): QObject(parent), m_frameHeight(0),
    m_frameWidth(0), m_currentFrame(0), m_paused(false), m_completed(false),
    m_desiredFrameRate(15)
{
    connect(&m_timer, &QTimer::timeout, this, &Animation::updateFrame);
}

Animation::~Animation() {
    m_timer.stop();
}

bool Animation::loadSpritesheet(const QString &filename, int frameWidth, int frameHeight) {
    m_spritesheet = QPixmap(filename);
    if (m_spritesheet.isNull())
    {
        return false;
    }

    m_frameWidth = frameWidth;
    m_frameHeight = frameHeight;

    return true;
}

void Animation::addState(const QString &name, int rowIndex, int frameCount, bool looping, bool movable, int direction)
{
    AnimationState state;
    state.name = name;
    state.rowIndex = rowIndex;
    state.frameCount = frameCount;
    state.looping = looping;
    state.movable = movable;
    state.direction = direction;
    state.flipHorizontally = (direction < 0);

    m_states[name] = state;

    if (m_currentStateName.isEmpty())
        setState(name);
}

QStringList Animation::availableStates() const {
    return m_states.keys();
}

// Add to Animation.cpp - setState method
bool Animation::setState(const QString& stateName) {

    if (!m_states.contains(stateName)) {
        return false;
    }


    if (m_currentStateName != stateName) {
        m_currentStateName = stateName;
        m_currentFrame = 0;
        m_completed = false;
        emit stateChanged(stateName);
        emit frameChanged(m_currentFrame);

    }

    return true;
}


void Animation::start(int frameRate) {
    m_currentFrame = 0;
    m_paused = false;
    m_completed = false;
    m_desiredFrameRate = frameRate;
    m_timer.start(1000 / frameRate);
    emit frameChanged(m_currentFrame);
}

void Animation::stop() {
    m_timer.stop();
    m_currentFrame = 0;
    m_paused = false;
    m_completed = false;
    emit frameChanged(m_currentFrame);
}

void Animation::pause() {
    if (m_timer.isActive()) {
        m_timer.stop();
        m_paused = true;
    }
}

void Animation::resume() {
    if (m_paused) {
        m_timer.start();
        m_paused = false;
    }
    else
        start(m_desiredFrameRate);
}

void Animation::setFrameRate(int frameRate) {
    m_desiredFrameRate = frameRate;
    if (isRunning())
        m_timer.setInterval(1000 / frameRate);
}

bool Animation::isLooping() const {
    if (!m_states.contains(m_currentStateName))
        return false;
    return m_states[m_currentStateName].looping;
}

bool Animation::isMovable() const {
    if (!m_states.contains(m_currentStateName))
        return false;
    return m_states[m_currentStateName].movable;
}

int Animation::direction() const {
    if (!m_states.contains(m_currentStateName))
        return 0;
    return m_states[m_currentStateName].direction;
}

QPoint Animation::getFramePosition(int stateRow, int frameIndex) const {
    int x = frameIndex * m_frameWidth;
    int y = stateRow * m_frameHeight;

    return QPoint(x, y);
}

// Animation.cpp - updateFrame method (fix the completion logic)
void Animation::updateFrame() {
    if (!m_states.contains(m_currentStateName)) {
        return;
    }

    const AnimationState& state = m_states[m_currentStateName];

    m_currentFrame++;

    if (m_currentFrame >= state.frameCount) {
        if (state.looping) {
            m_currentFrame = 0;
        } else {
            m_currentFrame = state.frameCount - 1;
            m_completed = true;
            m_timer.stop();

            emit animationCompleted(m_currentStateName);
            return;
        }
    }

    emit frameChanged(m_currentFrame);
}


// In Animation.cpp - Update currentFrame method
QPixmap Animation::currentFrame() const {
    if (m_spritesheet.isNull() || !m_states.contains(m_currentStateName)) {
        return QPixmap();
    }

    const AnimationState& state = m_states[m_currentStateName];
    if (m_currentFrame < 0 || m_currentFrame >= state.frameCount) {
        return QPixmap();
    }

    QPoint pos = getFramePosition(state.rowIndex, m_currentFrame);
    QPixmap frame = m_spritesheet.copy(pos.x(), pos.y(), m_frameWidth, m_frameHeight);

    // Apply horizontal flipping if needed
    if (state.flipHorizontally) {
        return frame.transformed(QTransform().scale(-1, 1));
    }

    return frame;
}


void Animation::setStateDirection(const QString &stateName, int direction) {
    if (!m_states.contains(stateName)) {
        return;
    }

    // Store the actual direction value
    m_states[stateName].direction = direction;
    // Update flip based on direction
    m_states[stateName].flipHorizontally = (direction < 0);

    if (m_currentStateName == stateName) {
        emit stateChanged(stateName);
    }
}



bool Animation::getStateFlip(const QString &stateName) const {
    if (!m_states.contains(stateName)) {
        return false;
    }

    return m_states[stateName].flipHorizontally;
}

// Implement in Animation.cpp
void Animation::dumpStateInfo() const {
    for (auto it = m_states.begin(); it != m_states.end(); ++it) {
        const QString& name = it.key();
        const AnimationState& state = it.value();
    }
}

int Animation::frameCount() const {
    if (!m_states.contains(m_currentStateName)) {
        return 0;
    }

    return m_states[m_currentStateName].frameCount;
}
