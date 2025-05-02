QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animation.cpp \
    enemy.cpp \
    gamewindow.cpp \
    gate.cpp \
    health.cpp \
    level1window.cpp \
    main.cpp \
    mainwindow.cpp \
    obstacle.cpp \
    player.cpp \
    pressuretile.cpp \
    score.cpp \
    spikes.cpp \
    tile.cpp

HEADERS += \
    animation.h \
    enemy.h \
    gamewindow.h \
    gate.h \
    health.h \
    level1window.h \
    mainwindow.h \
    obstacle.h \
    player.h \
    pressuretile.h \
    score.h \
    spikes.h \
    tile.h

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
