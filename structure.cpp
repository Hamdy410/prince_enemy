#include "structure.h"

Structure::Structure(int x, int y, int width, int height):
    QGraphicsRectItem(x, y, width, height)
{
}

Structure::~Structure()
{
}


void Structure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsRectItem::paint(painter, option, widget);
}
