#include "exit.h"

Exit::Exit(int x, int y)
    : Gate(QPointF(x, y))
    , is_activated(false)
{
    loadAnimationFrames();
}


void Exit::loadAnimationFrames()
{
    QPixmap spritesheet(":/images/exit.jpeg");

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
        frame = frame.scaled(114,144);
        m_frames.push_back(frame);
    }
}


void Exit::activate() {
    is_activated = true;
}


Exit::~Exit()
{
}
