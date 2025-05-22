#include "gamemanager.h"
#include "menupage.h"
#include "startpage.h"
#include "tutorialpage.h"
#include "level1window.h"
#include "level2window.h"
#include "level3window.h"
#include "level4window.h"
#include "level5window.h"
#include <QTimer>
#include <QMetaObject>

GameManager::GameManager(QObject* parent)
    : QObject(parent),
    m_menuPage(nullptr),
    m_currentWindow(nullptr),
    m_currentLevel(LEVEL_1) {

    // Initialize player states for each level
    PlayerState initialState = {15, 0}; // Default health and score
    m_playerStates[LEVEL_1] = initialState;
    m_playerStates[LEVEL_2] = initialState;
    m_playerStates[LEVEL_3] = initialState;
    m_playerStates[LEVEL_4] = initialState;
    m_playerStates[LEVEL_5] = initialState;

    // Create the menu page initially
    createMenuPage();
}

GameManager::~GameManager() {
    // Clean up any remaining windows
    cleanupCurrentWindow();
}

void GameManager::start() {
    if (m_menuPage) {
        m_menuPage->show();
    }
}

void GameManager::showMenuPage() {
    cleanupCurrentWindow();
    createMenuPage();
    m_menuPage->show();
}

void GameManager::showStartPage(LevelType level) {
    cleanupCurrentWindow();
    m_currentLevel = level;

    int levelNumber = static_cast<int>(level) + 1; // Convert to 1-based index
    StartPage* startPage = new StartPage("Prince of Persia", levelNumber);

    // Use a direct slot connection instead of a lambda
    connect(startPage, &StartPage::startRequested, this, [this]() {
        startLevel(m_currentLevel);
    });

    m_currentWindow = startPage;
    startPage->show();
}

void GameManager::showTutorialPage() {
    cleanupCurrentWindow();

    TutorialPage* tutorialPage = new TutorialPage();
    connect(tutorialPage, &TutorialPage::backToMenuRequested,
            this, &GameManager::showMenuPage);

    m_currentWindow = tutorialPage;
    tutorialPage->show();
}

void GameManager::saveCurrentLevelState() {
    // Save state based on current level
    switch (m_currentLevel) {
    case LEVEL_1:
        if (Level1Window* l1 = qobject_cast<Level1Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_1].health = l1->total_health;
            m_playerStates[LEVEL_1].score = l1->total_score;
        }
        break;
    case LEVEL_2:
        if (Level2Window* l2 = qobject_cast<Level2Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_2].health = l2->total_health;
            m_playerStates[LEVEL_2].score = l2->total_score;
        }
        break;
    case LEVEL_3:
        if (Level3Window* l3 = qobject_cast<Level3Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_3].health = l3->total_health;
            m_playerStates[LEVEL_3].score = l3->total_score;
        }
        break;
    case LEVEL_4:
        if (Level4Window* l4 = qobject_cast<Level4Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_4].health = l4->total_health;
            m_playerStates[LEVEL_4].score = l4->total_score;
        }
        break;
    case LEVEL_5:
        if (Level5Window* l5 = qobject_cast<Level5Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_5].health = l5->total_health;
            m_playerStates[LEVEL_5].score = l5->total_score;
        }
        break;
    }
}

void GameManager::startLevel(LevelType level) {
    cleanupCurrentWindow();
    m_currentLevel = level;

    GameWindow* levelWindow = nullptr;

    switch (level) {
    case LEVEL_1: {
        // Get health and score from previous state
        int health = m_playerStates[LEVEL_1].health;
        int score = m_playerStates[LEVEL_1].score;

        Level1Window* level1 = new Level1Window(nullptr, health, score);

        // Use QueuedConnection for safety
        connect(level1, &Level1Window::Level2Requested, this,
                &GameManager::onLevel1Completed, Qt::QueuedConnection);

        levelWindow = level1;
        break;
    }
    case LEVEL_2: {
        // Get health and score from previous state or level 1
        int health = m_playerStates[LEVEL_2].health;
        int score = m_playerStates[LEVEL_2].score;

        if (health == 15 && score == 0) {
            // If default values, use Level 1's values instead
            health = m_playerStates[LEVEL_1].health;
            score = m_playerStates[LEVEL_1].score;
        }

        Level2Window* level2 = new Level2Window(nullptr, health, score);

        // Use QueuedConnection for safety
        connect(level2, &Level2Window::Level3Requested, this,
                &GameManager::onLevel2Completed, Qt::QueuedConnection);

        levelWindow = level2;
        break;
    }
    case LEVEL_3: {
        // Get health and score from previous state or level 2
        int health = m_playerStates[LEVEL_3].health;
        int score = m_playerStates[LEVEL_3].score;

        if (health == 15 && score == 0) {
            // If default values, use Level 2's values instead
            health = m_playerStates[LEVEL_2].health;
            score = m_playerStates[LEVEL_2].score;
        }

        Level3Window* level3 = new Level3Window(nullptr, health, score);

        // Use QueuedConnection for safety
        connect(level3, &Level3Window::Level4Requested, this,
                &GameManager::onLevel3Completed, Qt::QueuedConnection);

        levelWindow = level3;
        break;
    }
    case LEVEL_4: {
        // Get health and score from previous state or level 3
        int health = m_playerStates[LEVEL_4].health;
        int score = m_playerStates[LEVEL_4].score;

        if (health == 15 && score == 0) {
            // If default values, use Level 3's values instead
            health = m_playerStates[LEVEL_3].health;
            score = m_playerStates[LEVEL_3].score;
        }

        Level4Window* level4 = new Level4Window(nullptr, health, score);

        // Use QueuedConnection for safety
        connect(level4, &Level4Window::Level5Requested, this,
                &GameManager::onLevel4Completed, Qt::QueuedConnection);

        levelWindow = level4;
        break;
    }
    case LEVEL_5: {
        // Get health and score from previous state or level 4
        int health = m_playerStates[LEVEL_5].health;
        int score = m_playerStates[LEVEL_5].score;

        if (health == 15 && score == 0) {
            // If default values, use Level 4's values instead
            health = m_playerStates[LEVEL_4].health;
            score = m_playerStates[LEVEL_4].score;
        }

        Level5Window* level5 = new Level5Window(nullptr, health, score);

        // Use QueuedConnection for safety
        connect(level5, &Level5Window::gameCompleted, this,
                &GameManager::onLevel5Completed, Qt::QueuedConnection);

        levelWindow = level5;
        break;
    }
    }

    if (levelWindow) {
        m_currentWindow = levelWindow;
        levelWindow->show();
    }
}

void GameManager::onLevel1Completed() {
    saveCurrentLevelState();
    handleLevelCompletion(LEVEL_1);
}

void GameManager::onLevel2Completed() {
    saveCurrentLevelState();
    handleLevelCompletion(LEVEL_2);
}

void GameManager::onLevel3Completed() {
    saveCurrentLevelState();
    handleLevelCompletion(LEVEL_3);
}

void GameManager::onLevel4Completed() {
    saveCurrentLevelState();
    handleLevelCompletion(LEVEL_4);
}

void GameManager::onLevel5Completed() {
    saveCurrentLevelState();
    // Return to menu page after game completion
    showMenuPage();
}

void GameManager::handleLevelCompletion(LevelType completedLevel) {
    // Move to next level
    LevelType nextLevel = static_cast<LevelType>(static_cast<int>(completedLevel) + 1);

    // Create a single-shot timer that deletes itself after firing
    QTimer* transitionTimer = new QTimer(this);
    transitionTimer->setSingleShot(true);

    connect(transitionTimer, &QTimer::timeout, this, [this, nextLevel, transitionTimer]() {
        showStartPage(nextLevel);
        transitionTimer->deleteLater();
    });

    // Start the timer before cleaning up the window
    transitionTimer->start(500);

    // Now safe to clean up the current window
    cleanupCurrentWindow();
}

void GameManager::cleanupCurrentWindow() {
    if (m_currentWindow) {
        // Only disconnect signals connected to this GameManager
        m_currentWindow->disconnect(this);

        // Close and delete the window
        m_currentWindow->close();
        m_currentWindow->deleteLater(); // Use deleteLater instead of delete for safety
        m_currentWindow = nullptr;
    }
}

void GameManager::createMenuPage() {
    m_menuPage = new MenuPage("Prince of Persia");

    connect(m_menuPage, &MenuPage::playGameRequested, this, [this]() {
        showStartPage(LEVEL_1);
    });

    connect(m_menuPage, &MenuPage::tutorialRequested, this,
            &GameManager::showTutorialPage);

    m_currentWindow = m_menuPage;
}
