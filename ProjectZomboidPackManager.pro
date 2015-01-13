#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T06:56:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectZomboidPackManager
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        packmanagermainwindow.cpp \
    packfilemetadata.cpp \
    packfilepagemetadata.cpp \
    packentrymetadata.cpp \
    texturesplitter.cpp \
    texturemerger.cpp \
    texturepacker.cpp \
    threadabletask.cpp \
    textureunpacker.cpp

HEADERS  += packmanagermainwindow.h \
    packfilemetadata.h \
    packfilepagemetadata.h \
    packentrymetadata.h \
    texturesplitter.h \
    texturemerger.h \
    texturepacker.h \
    threadabletask.h \
    textureunpacker.h

FORMS    += packmanagermainwindow.ui
