#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T18:56:14
#
#-------------------------------------------------

QT       += quick

QT       -= gui

TARGET = utils
TEMPLATE = lib

DEFINES += UTILS_LIBRARY

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
    bonustimer.cpp \
    collider.cpp \
    gameresult.cpp \
    stageiterator.cpp \
    bcsreader.cpp

HEADERS += \
        utils_global.h \ 
    bonustimer.h \
    collider.h \
    gameresult.h \
    stageiterator.h \
    bcsreader.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../base/release/ -lbase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../base/debug/ -lbase
else:unix: LIBS += -L$$OUT_PWD/../base/ -lbase

INCLUDEPATH += $$PWD/../base
DEPENDPATH += $$PWD/../base
