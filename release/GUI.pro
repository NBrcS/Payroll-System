QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edit.cpp \
    empresa.cpp \
    finaledit.cpp \
    financial.cpp \
    main.cpp \
    mainwindow.cpp \
    paymentsheet.cpp

HEADERS += \
    edit.h \
    empresa.h \
    finaledit.h \
    financial.h \
    mainwindow.h \
    paymentsheet.h

FORMS += \
    edit.ui \
    finaledit.ui \
    financial.ui \
    mainwindow.ui \
    paymentsheet.ui

TRANSLATIONS += \
    GUI_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
