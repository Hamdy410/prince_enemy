#ifndef TRANSITION_H
#define TRANSITION_H

#include <QWidget>
#include "structure.h"

class Transition : public Structure
{

public:
    explicit Transition(int x, int y, int width, int height);
    ~Transition();

};

#endif // TRANSITION_H
