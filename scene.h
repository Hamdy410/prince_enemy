#ifndef SCENE_H
#define SCENE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <string>
#include <QGraphicsView>

namespace Ui {
class Scene;
}

class Scene : public QDialog
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr, int order = 1);
    ~Scene();

private:
    Ui::Scene *ui;
};

#endif // SCENE_H
