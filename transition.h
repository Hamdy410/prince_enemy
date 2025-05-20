#ifndef TRANSITION_H
#define TRANSITION_H

#include <QWidget>
#include "structure.h"

class Transition : public Structure
{
    Q_OBJECT

public:
    explicit Transition(int x, int y, int width, int height, QString label, int next_scene);
    ~Transition();

private:
    int next_scene;
};

#endif // TRANSITION_H
