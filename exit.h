#ifndef EXIT_H
#define EXIT_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include "gate.h"


class Exit : public Gate
{
    Q_OBJECT

public:
    explicit Exit(int x, int y);
    void loadAnimationFrames();
    void activate();
    ~Exit();

private:
    bool is_activated;
};

#endif // EXIT_H
