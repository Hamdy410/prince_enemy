#include "score.h"
#include <QPainter>

Score::Score() : points(0) {}
void Score::increase(int amount) { points += amount; }
void Score::draw(QPainter *painter, int x, int y) const {
    QFont font("Times", 16, QFont::Bold);
    painter->setFont(font);
    painter->setPen(Qt::darkBlue);
    painter->drawText(x, y, QString("Score: %1").arg(points));
}
