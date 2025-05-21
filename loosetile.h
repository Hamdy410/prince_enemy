#ifndef LOOSETILE_H
#define LOOSETILE_H
#include <QObject>
#include "tile.h"
#include <QPixmap>
#include <QTimer>

class LooseTile :public QObject, public tile
{
   Q_OBJECT
public:
    // Tile states
    enum State {
        Idle,
        Shaking1,
        Shaking2,
        Disappearing
    };

    // Constructor/Destructor
    LooseTile(int x, int y, bool hasEnemy, int width, int height);
    ~LooseTile();

    // Public functions
    void setPressed(bool pressed);
    void startBreakSequence();
    void resetTile();
    QRectF activationRegion() const;

    // Painting functions
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void draw(QPainter* painter);

protected:
    void advanceAnimation();

private:
    // Helper functions
    void loadImages();

    // State variables
    bool m_pressed;
    int m_normalY;
    int m_pressedY;
    State m_state;
    int m_shakeCount;

    // Image resources
    QPixmap* m_idleImage;
    QPixmap* m_shaking1Image;
    QPixmap* m_shaking2Image;

    // Timers
    QTimer* m_animTimer;
    QTimer* m_disappearTimer;
};

#endif // LOOSETILE_H
