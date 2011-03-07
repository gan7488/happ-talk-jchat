QT       += core gui svg

TARGET = happ-talk-jchat
TEMPLATE = app
#LIBS += -lgloox

SOURCES += main.cpp \
    maindialog.cpp \
    aboutdialog.cpp \
    configdialog.cpp \
    talksdialog.cpp \
    talkerinfowidget.cpp \
    talkwidget.cpp \
    roominfowidget.cpp \
    generalconfigwidget.cpp \
    chatconfigwidget.cpp \
    proxyconfigwidget.cpp \
    logindialog.cpp

HEADERS  += \
    maindialog.h \
    aboutdialog.h \
    configdialog.h \
    talksdialog.h \
    talkerinfowidget.h \
    talkwidget.h \
    roominfowidget.h \
    generalconfigwidget.h \
    chatconfigwidget.h \
    proxyconfigwidget.h \
    logindialog.h

OTHER_FILES += \
    readme.txt

RESOURCES += \
    resources.qrc
