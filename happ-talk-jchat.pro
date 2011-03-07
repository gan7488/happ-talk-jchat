QT       += core gui svg

TARGET = happ-talk-jchat
TEMPLATE = app
#LIBS += -lgloox

SOURCES += main.cpp \
    maindialog.cpp \
    aboutdialog.cpp \
    configdialog.cpp \
    talksdialog.cpp \
    chatwidget.cpp \
    talkerinfowidget.cpp \
    roominfowidget.cpp \
    talkwidget.cpp

HEADERS  += \
    maindialog.h \
    aboutdialog.h \
    configdialog.h \
    talksdialog.h \
    chatwidget.h \
    talkerinfowidget.h \
    roominfowidget.h \
    talkwidget.h

OTHER_FILES += \
    readme.txt

RESOURCES += \
    resources.qrc
