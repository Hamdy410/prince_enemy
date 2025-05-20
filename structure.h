#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<QPainter>
#include <QWidget>
#include <QGraphicsRectItem>


class Structure : public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Structure(int x, int y, int width, int height, QString label);
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    ~Structure();
    QString what_label() {return label;};

private:
    QString label;
};

#endif // STRUCTURE_H
