#include "transition.h"

Transition::Transition(int x, int y, int width, int height, QString label, int next_scene)
    : Structure(x, y, width, height, label)
    , next_scene(next_scene)
{
}

Transition::~Transition()
{
}
