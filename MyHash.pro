#-------------------------------------------------
#
# Project created by QtCreator 2013-05-29T18:19:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyHash
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gost3411-2012-core.c

HEADERS  += mainwindow.h \
    gost3411-2012-ref.h \
    gost3411-2012-precalc.h \
    gost3411-2012-core.h \
    gost3411-2012-const.h \
    gost3411-2012-sse41.h \
    gost3411-2012-sse2.h \
    gost3411-2012-mmx.h \
    gost3411-2012-config.h

FORMS    += mainwindow.ui
