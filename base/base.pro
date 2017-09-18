#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T18:53:55
#
#-------------------------------------------------

QT       += quick

QT       -= gui

TARGET = base
TEMPLATE = lib

DEFINES += BASE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseitem.cpp \
    bcobject.cpp \
    board.cpp \
    global.cpp \
    informationpanel.cpp \
    movableitem.cpp \
    shootableitem.cpp \
    tile.cpp

HEADERS += \
        base_global.h \ 
    baseitem.h \
    bcobject.h \
    board.h \
    global.h \
    informationpanel.h \
    movableitem.h \
    shootableitem.h \
    tile.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
