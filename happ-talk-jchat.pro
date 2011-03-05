#-------------------------------------------------
#
# Project created by QtCreator 2011-02-22T17:27:47
#
#-------------------------------------------------

QT       += core gui svg

TARGET = happ-talk-jchat
TEMPLATE = app

LIBS += -lgloox

SOURCES += main.cpp \
    mainwindow.cpp \
    imwidget.cpp \
    configdialog.cpp \
    aboutdialog.cpp

HEADERS  += \
    mainwindow.h \
    imwidget.h \
    configdialog.h \
    aboutdialog.h

FORMS    += \
    mainwindow.ui \
    imwidget.ui \
    configdialog.ui

OTHER_FILES += \
    README.txt

RESOURCES += \
    resources.qrc
