/*
 * Author: Kareem Adel
 * Start Date:
 * End Date:
 */

#ifndef HEALTH_H
#define HEALTH_H

#include <QPainter>


class Health {
public:
    Health(int maxHealth = 100);
    void decrease(int amount = 1);
    void increase(int amount = 1);
    void reset(){value=15;}
    void draw(QPainter* painter, int x, int y, int width = 200, int height = 20) const;
    int getHealth(){return value;}
private:
    int value;
    int maxValue;
};


#endif // HEALTH_H
