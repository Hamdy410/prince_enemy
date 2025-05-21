#include "wall.h"
#include <QRectF>

/*void tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Draw your player sprite/image first (if any)
    painter->drawPixmap(0, 0, pixmap());
    // Draw the bounding rect with color
    painter->setPen(QPen(Qt::green, 2));      // Red outline, 2px thick
    painter->setBrush(Qt::transparent);        // Transparent fill
    painter->drawRect(boundingrect);      // Draw the bounding rectangle
}
*/

wall::wall(int x, int y,int width , int height,bool right)
    : QGraphicsRectItem(x,y,width,height),isRight(right){
    setPos(x,y);
    boundingrect = boundingRect();
}

void wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsRectItem::paint(painter, option, widget);
}
