/*
 * Author: Hamdy El-Madbouly
 * Start Date: 17 Dec, 2025
 * End Date:
 * Description:
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include "transition.h"
#include "enemy.h"
#include "tile.h"
#include "player.h"
#include "spikes.h"
#include "gate.h"
#include "chopper.h"
#include "wall.h"
#include "ceiling.h"
#include "transition.h"
#include "exit.h"
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, int healthVal=15, int scoreVal=0);
    void setFundementals(int x, int y,int width, int height,QString BackUrl = "",QString FrontUrl = "", int posX=-1, int posY=-1){
        Background = new QPixmap(BackUrl);
        Foreground = new QPixmap(FrontUrl);
        transitionX = x;
        transitionY = y;
        transitionWidth = width;
        transitionHeight = height;
        PositionPlayerx=posX;
        PositionPlayery=posY;
    }
    ~GameWindow();
protected:
    void initializeGame();
    void stopGame();
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    virtual void createTilesandWallsandCeiling();
    QList<tile*> createTiles(int startX, int y, int count, int tileWidth = 60, int tileHeight = 2,
                              bool createEnemy = false, int overlap=10,
                              const QList<int>& spikeIndices = QList<int>(),
                              const QList<int>& pressureIndices = QList<int>(),
                              const QList<int>& gateIndices = QList<int>(), const QList<int>& choppersIndices = QList<int>());
    void addExit(int x, int y);
    QList<wall*> createWalls(int startX, int y,int width, int height, bool right);
    QList<ceiling*>createCeiling(int startX, int y,int width, int height);
    QList<tile*> m_tiles;
    QList<Spikes*> m_spikes;
    QList<Gate*> m_gates;
    QList<Chopper*>m_choppers;
    QList<wall*>m_walls;
    QList<ceiling*>m_ceilings;
    QMap<int, int> m_tileToGateMap;
    player *m_player;
    int total_health;
    int total_score;
    Exit* exit;
    virtual void getNextRoom();
    virtual void getCurrentRoom(){}
    void connectPressureTileToGate(int pressureTileIndex, int gateIndex);

    QTimer m_gameTimer;

private slots:
    void updateGame();
    void toggleDebugMode() { m_debugMode = !m_debugMode; update(); }

private:
    void drawDebugInfo(QPainter *painter);
    QString stateToString(Enemy::State state) const;

    QList<Enemy*> m_enemies;
    bool m_debugMode;
    int m_frameCounter;
    int m_fps;
    Transition* transition;
    int transitionX;
    int transitionY;
    int transitionWidth;
    int transitionHeight;
    int PositionPlayerx;
    int PositionPlayery;
    QElapsedTimer m_fpsTimer;
    bool m_gameOver = false;
    QPixmap *Background;
    QPixmap *Foreground;
};

#endif // GAMEWINDOW_H
