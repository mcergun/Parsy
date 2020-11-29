TEMPLATE = lib
CONFIG += c++11
CONFIG += dll
CONFIG -= qt

DEFINES += BITGRABBER_EXPORT

win32
{
    CONFIG(debug, debug|release): dllcopydir = $$OUT_PWD/../cli/debug
    else: dllcopydir = $$OUT_PWD/../cli/release
    DLLDESTDIR = $$dllcopydir
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
