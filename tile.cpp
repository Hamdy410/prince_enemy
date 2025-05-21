#include "tile.h"
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

tile::tile(int x, int y, bool hasEnemy,int width , int height)
    : QGraphicsRectItem(x,y,width,height)
    , m_hasEnemy(hasEnemy) {
    //QPixmap SpriteSheet(":/images/EnvironSpriteOK.png");
    //setPixmap(SpriteSheet.copy(127, 685, 60, 18));
    setPos(x,y);
    groundy = y;
    boundingrect = boundingRect();
}

void tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsRectItem::paint(painter, option, widget);
}
