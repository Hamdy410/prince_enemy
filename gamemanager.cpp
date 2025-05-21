#include "gamemanager.h"
#include "menupage.h"
#include "startpage.h"
#include "tutorialpage.h"
#include "level1window.h"
#include "level2window.h"
#include "level3window.h"
#include <QTimer>
#include <QMetaObject>

GameManager::GameManager(QObject* parent)
    : QObject(parent),
    m_menuPage(nullptr),
    m_currentWindow(nullptr),
    m_currentLevel(LEVEL_1),
    m_playerHealth(15),
    m_playerScore(0) {

    // Initialize player states for each level
    PlayerState initialState = {15, 0}; // Default health and score
    m_playerStates[LEVEL_1] = initialState;
    m_playerStates[LEVEL_2] = initialState;
    m_playerStates[LEVEL_3] = initialState;

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
            // Save other state if needed
        }
        break;
    case LEVEL_2:
        if (Level2Window* l2 = qobject_cast<Level2Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_2].health = l2->total_health;
            // Save other state if needed
        }
        break;
    case LEVEL_3:
        if (Level3Window* l3 = qobject_cast<Level3Window*>(m_currentWindow)) {
            m_playerStates[LEVEL_3].health = l3->total_health;
            // Save other state if needed
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
        Level1Window* level1 = new Level1Window();
        // Set player health/score from stored state
        level1->PositionPlayerx = 0;
        level1->PositionPlayery = 0;
        level1->total_health = m_playerStates[LEVEL_1].health;

        // Use QueuedConnection for safety
        connect(level1, &Level1Window::Level2Requested, this,
                &GameManager::onLevel1Completed, Qt::QueuedConnection);

        levelWindow = level1;
        break;
    }
    case LEVEL_2: {
        Level2Window* level2 = new Level2Window();
        // Set player health/score from stored state or from level 1
        level2->PositionPlayerx = 0;
        level2->PositionPlayery = 0;
        level2->total_health = m_playerStates[LEVEL_1].health; // Carry over health from level 1

        // We need to connect to a signal that Level2Window should emit
        // This is done using the old-style connection since Level2Window doesn't have the signal declared yet
        connect(level2, SIGNAL(Level3Requested()), this, SLOT(onLevel2Completed()), Qt::QueuedConnection);

        levelWindow = level2;
        break;
    }
    case LEVEL_3: {
        Level3Window* level3 = new Level3Window();
        // Set player health/score from stored state or from level 2
        level3->PositionPlayerx = 0;
        level3->PositionPlayery = 0;
        level3->total_health = m_playerStates[LEVEL_2].health; // Carry over health from level 2

        // Connect to a signal that Level3Window should emit
        connect(level3, SIGNAL(GameCompleted()), this, SLOT(onLevel3Completed()), Qt::QueuedConnection);

        levelWindow = level3;
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
    // Handle game completion - maybe show a victory screen
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
