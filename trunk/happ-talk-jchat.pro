#-------------------------------------------------
#
# Project created by QtCreator 2011-02-22T17:27:47
#
#-------------------------------------------------

QT       += core gui svg

TARGET = happ-talk-jchat
TEMPLATE = app

#LIBS += -lgloox

SOURCES += main.cpp \
    aboutdialog.cpp \
    mainwindow.cpp \
    imwindow.cpp \
    imwidget.cpp \
    roomwidget.cpp \
    roomconfigwidget.cpp \
    settings.cpp \
    userinfowidget.cpp \
    roominfowidget.cpp

HEADERS  += \
    aboutdialog.h \
    mainwindow.h \
    imwindow.h \
    imwidget.h \
    roomwidget.h \
    roomconfigwidget.h \
    settings.h \
    userinfowidget.h \
    roominfowidget.h

FORMS    +=

OTHER_FILES += \
    README.txt

RESOURCES += \
    resources.qrc
