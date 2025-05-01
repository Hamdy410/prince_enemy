#ifndef LEVEL1WINDOW_H
#define LEVEL1WINDOW_H

#include "gamewindow.h"

class Level1Window : public GameWindow
{
public:
    explicit Level1Window(QWidget* parent = nullptr);
protected:
    using GameWindow::createTiles;
    void createTiles() override;
};

#endif // LEVEL1WINDOW_H
