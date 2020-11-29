TEMPLATE = lib
CONFIG += c++11
CONFIG += dll
CONFIG -= qt

DEFINES += BITGRABBER_EXPORT

win32
{
    DLLDESTDIR = $$PWD/../build/cli
}

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
