#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QMap>
#include <QVector>

struct AnimationState
{
    QString name;           // State identifier
    int rowIndex;           // Row in spritesheet
    int frameCount;         // Number of frames in this state
    bool looping;           // Should the animation loop?
    bool movable;           // Does the entity move during this state?
    int direction;          // Movement direction: 1=right; -1=left; 0=stationary
    bool flipHorizontally;  // Whether to flip the sprite horizontally
};

class Animation : public QObject
{
    Q_OBJECT

public:
    explicit Animation(QObject* parent = nullptr);
    ~Animation();

    // Load sprite and setup
    bool loadSpritesheet(const QString& filename, int frameWidth, int frameHeight);

    // State Management
    void addState(const QString& name, int rowIndex, int frameCount, bool looping=true, bool movable=false, int direction=0);
    bool setState(const QString& stateName);
    QString currentState() const { return m_currentStateName; }
    QStringList availableStates() const;

    // Animation Control
    void start(int frameRate = 15);
    void stop();
    void pause();
    void resume();
    void setFrameRate(int frameRate);

    // Status Information
    bool isRunning() const { return m_timer.isActive(); }
    bool isPaused() const { return m_paused; }
    bool isLooping() const;
    bool isMovable() const;
    int direction() const;
    bool hasCompleted() const { return m_completed; }

    // Frame Information
    QPixmap currentFrame() const;
    int currentFrameIndex() const { return m_currentFrame; }
    int frameWidth() const { return m_frameWidth; }
    int frameHeight() const { return m_frameHeight; }

    QTimer m_timer;

    int desiredFrameRate() const { return m_desiredFrameRate; }
    void setStateDirection(const QString& stateName, int direction);
    bool getStateFlip(const QString& stateName) const;

    void dumpStateInfo() const;
    int frameCount() const;


signals:
    void frameChanged(int frameIndex);
    void stateChanged(const QString& stateName);
    void animationCompleted(const QString& stateName);

private slots:
    void updateFrame();

private:
    QPoint getFramePosition(int stateRow, int frameIndex) const;

    QPixmap m_spritesheet;
    QMap<QString, AnimationState> m_states;
    QString m_currentStateName;
    int m_frameWidth;
    int m_frameHeight;
    int m_currentFrame;
    bool m_paused;
    bool m_completed;
    int m_desiredFrameRate;
};

#endif // ANIMATION_H
