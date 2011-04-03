QT       += core gui svg
#CONFIG += static

TARGET = happ-talk-jchat
TEMPLATE = app
LIBS += -LD:\Projects\Programming.Qt\happ-talk-jchat-build-desktop\debug -lgloox
#LIBS += -lgloox

SOURCES += main.cpp \
    ui/maindialog.cpp \
    ui/aboutdialog.cpp \
    ui/configdialog.cpp \
    ui/talksdialog.cpp \
    ui/logindialog.cpp \
    ui/widgets/talkerinfowidget.cpp \
    ui/widgets/talkwidget.cpp \
    ui/widgets/roominfowidget.cpp \
    ui/widgets/generalconfigwidget.cpp \
    ui/widgets/chatconfigwidget.cpp \
    ui/widgets/proxyconfigwidget.cpp \
    ui/widgets/messagewidget.cpp \
    xmpp/jclient.cpp \
    xmpp/jregisterclient.cpp \
    xmpp/xmppclient.cpp \
    xmpp/xmppregistration.cpp \
    xmpp/xmppmessaging.cpp

HEADERS  += \
    consts.h \
    ui/maindialog.h \
    ui/aboutdialog.h \
    ui/configdialog.h \
    ui/talksdialog.h \
    ui/logindialog.h \
    ui/widgets/talkerinfowidget.h \
    ui/widgets/talkwidget.h \
    ui/widgets/roominfowidget.h \
    ui/widgets/generalconfigwidget.h \
    ui/widgets/chatconfigwidget.h \
    ui/widgets/proxyconfigwidget.h \
    ui/widgets/messagewidget.h \
    xmpp/jclient.h \
    xmpp/jregisterclient.h \
    xmpp/xmppclient.h \
    xmpp/xmppregistration.h \
    xmpp/xmppclientextension.h \
    xmpp/xmppmessaging.h

OTHER_FILES += \
    readme.txt

RESOURCES += \
    resources.qrc
