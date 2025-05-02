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

#include "enemy.h"
#include "tile.h"
#include "player.h"
#include "spikes.h"
#include "gate.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void initializeGame();
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    virtual void createTiles();
    QList<tile*> createTiles(int startX, int y, int count, int tileWidth = 60,
                            bool createEnemy = false, int overlap=10,
                            const QList<int>& spikeIndices = QList<int>(),
                            const QList<int>& pressureIndices = QList<int>(),
                            const QList<int>& gateIndices = QList<int>());
    QList<tile*> m_tiles;
    QList<Spikes*> m_spikes;
    QList<Gate*> m_gates;
    QMap<int, int> m_tileToGateMap;

private slots:
    void updateGame();
    void toggleDebugMode() { m_debugMode = !m_debugMode; update(); }

private:
    void drawDebugInfo(QPainter *painter);
    QString stateToString(Enemy::State state) const;

    player *m_player;
    QList<Enemy*> m_enemies;

    QTimer m_gameTimer;
    bool m_debugMode;
    int m_frameCounter;
    int m_fps;
    QElapsedTimer m_fpsTimer;

    bool m_gameOver = false;
};

#endif // GAMEWINDOW_H
