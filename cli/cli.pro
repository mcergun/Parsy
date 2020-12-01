TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../parsy/release/ -lparsy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../parsy/debug/ -lparsy
else:unix: LIBS += -L$$OUT_PWD/../parsy/ -lparsy

INCLUDEPATH += $$PWD/../parsy
DEPENDPATH += $$PWD/../parsy

DEFINES += _CRT_SECURE_NO_WARNINGS

TARGET = parsy-cli

SOURCES += \
        main.cpp
