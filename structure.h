#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<QPainter>
#include <QWidget>
#include <QGraphicsRectItem>


class Structure : public QGraphicsRectItem
{

public:
    explicit Structure(int x, int y, int width, int height);
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    ~Structure();

};

#endif // STRUCTURE_H
