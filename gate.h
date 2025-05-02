#ifndef GATE_H
#define GATE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QVector>

class Gate : public QObject, public QGraphicsPixmapItem
{
public:
    Gate(const QPointF& pos);
    ~Gate();

    bool isSolid() const { return !m_isOpen; }
    bool isOpen() const { return m_isOpen; }

    static constexpr int SINK_OFFSET = 40;

public slots:
    void Open();
    void Close();

private slots:
    void updateAnimation();

private:
    void loadAnimationFrames();

    bool m_isOpen;
    bool m_isAnimating;
    bool m_isOpening;

    int m_currentFrame;
    int m_totalFrames;
    QVector<QPixmap> m_frames;

    QTimer m_animationTimer;
    static constexpr int FRAME_DURATION = 100;
};

#endif // GATE_H
