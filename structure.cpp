#include "structure.h"

Structure::Structure(int x, int y, int width, int height, QString label):
    QGraphicsRectItem(x, y, width, height),
    label(label)
{
}

Structure::~Structure()
{
}


void Structure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsRectItem::paint(painter, option, widget);
}
