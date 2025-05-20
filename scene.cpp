#include "scene.h"
#include "ui_scene.h"

Scene::Scene(QWidget *parent, int order)
    : QDialog(parent)
    , ui(new Ui::Scene)
{
    ui->setupUi(this);
    // BACKGROUND CODE DO NOT DELETE THIS
    // QPixmap back(QString::fromStdString(":/background/lvl1-scn" + std::to_string(order) + "-back"));
    // QGraphicsPixmapItem* backG = new QGraphicsPixmapItem(back);

    // ADD YOUR TILES AND CHARACTERS HERE


    QGraphicsScene* scene = new QGraphicsScene(0, 0, 320, 202);
    // DON'T DELETE THIS EITHER
    // scene->addItem(backG);

    // LINK YOUR TILES AND CHARACTERS TO THE SCENE

    QGraphicsView* view = new QGraphicsView;
    view->setScene(scene);
    view->setFixedSize(320, 202);
    // There is a ~7px blank space at the bottom of the screen. This is INTENTIONAL for the heart/lives trackers.
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
}

Scene::~Scene()
{
    delete ui;
}
