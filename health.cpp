#include "health.h"

Health::Health(int maxHealth) : value(maxHealth), maxValue(maxHealth) {}

void Health::decrease(int amount) {
    value -= amount;
    if (value < 0) value = 0;
}

void Health::increase(int amount) {
    value += amount;
    if (value > maxValue) value = maxValue;
}

void Health::draw(QPainter *painter, int x, int y, int width, int height) const {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(x, y, width, height);

    painter->setBrush(Qt::red);
    int healthWidth = (value * width) / maxValue;
    painter->drawRect(x, y, healthWidth, height);

    painter->setPen(Qt::black);
    painter->drawText(x + 5, y + height - 5, QString("Health: %1").arg(value));
}
