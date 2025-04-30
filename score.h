/*
 * Author: Kareem Adel
 * Start Date:
 * End Date:
 */

#ifndef SCORE_H
#define SCORE_H

#include <QPainter>
class Score {
public:
    Score();
    void increase(int amount);
    void reset() { points = 0; }
    int value() const { return points; }
    void draw(QPainter* painter, int x, int y) const;
private:
    int points;
};


#endif // SCORE_H
