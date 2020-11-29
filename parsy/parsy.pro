TEMPLATE = lib
CONFIG += c++11
CONFIG += dynamiclib
CONFIG -= qt

DEFINES += BITGRABBER_EXPORT

SOURCES += \
        BitGrabber.cpp \
        FileEntry.cpp \
        StringGrabber.cpp

HEADERS += \
    BitGrabber.h \
    DllExports.h \
    EndianConverter.h \
    FileEntry.h \
    StringGrabber.h
