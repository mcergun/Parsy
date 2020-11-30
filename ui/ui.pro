QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../parsy/release/ -lparsy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../parsy/debug/ -lparsy
else:unix: LIBS += -L$$OUT_PWD/../parsy/ -lparsy

INCLUDEPATH += $$PWD/../parsy
DEPENDPATH += $$PWD/../parsy

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileEntryTableModel.cpp \
    grammarwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FileEntryTableModel.h \
    grammarwindow.h \
    mainwindow.h

FORMS += \
    grammarwindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    ui_tr_TR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
