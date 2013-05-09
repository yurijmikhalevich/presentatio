#-------------------------------------------------
#
# Project created by QtCreator 2013-02-10T21:09:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = presentatio
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

SOURCES += \
quazip/JlCompress.cpp \
quazip/qioapi.cpp \
quazip/quaadler32.cpp \
quazip/quacrc32.cpp \
quazip/quagzipfile.cpp \
quazip/quaziodevice.cpp \
quazip/quazipdir.cpp \
quazip/quazipfile.cpp \
quazip/quazipnewinfo.cpp \
quazip/unzip.c \
quazip/zip.c \
quazip/quazip.cpp

HEADERS += \
quazip/crypt.h \
quazip/ioapi.h \
quazip/JlCompress.h \
quazip/quaadler32.h \
quazip/quachecksum32.h \
quazip/quacrc32.h \
quazip/quagzipfile.h \
quazip/quaziodevice.h \
quazip/quazipdir.h \
quazip/quazipfile.h \
quazip/quazipfileinfo.h \
quazip/quazip_global.h \
quazip/quazip.h \
quazip/quazipnewinfo.h \
quazip/unzip.h \
quazip/zip.h
