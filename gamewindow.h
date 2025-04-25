#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include "enemy.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateGame();
    void toggleDebugMode() { m_debugMode = !m_debugMode; update(); }

private:
    void initializeGame();
    void centerEnemyVertically();
    void drawDebugInfo(QPainter *painter);
    QString stateToString(Enemy::State state) const;

    Enemy *m_enemy;
    QTimer m_gameTimer;
    bool m_debugMode;
    int m_frameCounter;
    int m_fps;
    QElapsedTimer m_fpsTimer;
};

#endif // GAMEWINDOW_H
