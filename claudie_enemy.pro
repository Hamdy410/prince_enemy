QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animation.cpp \
    ceiling.cpp \
    chopper.cpp \
    coin.cpp \
    enemy.cpp \
    exit.cpp \
    gamewindow.cpp \
    gate.cpp \
    health.cpp \
    level1window.cpp \
    level2window.cpp \
    level3window.cpp \
    level4window.cpp \
    level5window.cpp \
    loosetile.cpp \
    main.cpp \
    mainwindow.cpp \
    menupage.cpp \
    obstacle.cpp \
    player.cpp \
    player_animation.cpp \
    pressuretile.cpp \
    score.cpp \
    spikes.cpp \
    startpage.cpp \
    structure.cpp \
    tile.cpp \
    transition.cpp \
    tutorialpage.cpp \
    wall.cpp

HEADERS += \
    animation.h \
    ceiling.h \
    chopper.h \
    coin.h \
    enemy.h \
    exit.h \
    gamewindow.h \
    gate.h \
    health.h \
    level1window.h \
    level2window.h \
    level3window.h \
    level4window.h \
    level5window.h \
    loosetile.h \
    mainwindow.h \
    menupage.h \
    obstacle.h \
    player.h \
    player_animation.h \
    pressuretile.h \
    score.h \
    spikes.h \
    startpage.h \
    structure.h \
    tile.h \
    transition.h \
    tutorialpage.h \
    wall.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG(release, debug|release): DEFINES += QT_NO_INFO_OUTPUT
CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT

