#include "exit.h"

Exit::Exit(int x, int y, int width, int height, QString label, int next_level)
    : Gate(QPointF(x, y))
    , next_level(next_level)
    , is_activated(false)
    , width(width)
    , height(height)
{
}


void Exit::loadAnimationFrames()
{
    QPixmap spritesheet(":/images/exit.png");

    if (spritesheet.isNull()) {
        return;
    }

    int columns = 16;
    int frameWidth = width;
    int frameHeight = height;

    m_totalFrames = columns;
    m_frames.clear();

    for (int i = 0; i < columns; ++i) {
        QPixmap frame = spritesheet.copy(i * frameWidth, 0, frameWidth, frameHeight);
        m_frames.push_back(frame);
    }
}


void Exit::activate() {
    is_activated = true;
}


Exit::~Exit()
{
}
