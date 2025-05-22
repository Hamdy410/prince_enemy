#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QMap>

class MenuPage;
class StartPage;
class TutorialPage;
class Level1Window;
class Level2Window;
class Level3Window;
class Level4Window;
class Level5Window;
class GameWindow;

class GameManager : public QObject {
    Q_OBJECT

public:
    enum LevelType {
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,
        LEVEL_5
    };

    GameManager(QObject* parent = nullptr);
    ~GameManager();

    void start();

private slots:
    void showMenuPage();
    void showStartPage(LevelType level);
    void showTutorialPage();
    void startLevel(LevelType level);
    void handleLevelCompletion(LevelType completedLevel);

    // Helper slots for level completion
    void onLevel1Completed();
    void onLevel2Completed();
    void onLevel3Completed();
    void onLevel4Completed();
    void onLevel5Completed();

private:
    void cleanupCurrentWindow();
    void createMenuPage();
    void saveCurrentLevelState();

    MenuPage* m_menuPage;
    QWidget* m_currentWindow;
    LevelType m_currentLevel;

    // Store player state between levels
    struct PlayerState {
        int health;
        int score;
    };

    QMap<LevelType, PlayerState> m_playerStates;
};

#endif // GAMEMANAGER_H
