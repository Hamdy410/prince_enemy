#ifndef EXIT_H
#define EXIT_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include "gate.h"


class Exit : public Gate
{
    Q_OBJECT

public:
    explicit Exit(int x, int y, int width, int height, QString label, int next_level);
    void loadAnimationFrames();
    void activate();
    ~Exit();

private:
    int next_level;
    bool is_activated;
    int width;
    int height;
};

#endif // EXIT_H
