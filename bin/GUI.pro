QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data.cpp \
    diretor.cpp \
    edit.cpp \
    empresa.cpp \
    exihibition.cpp \
    finaledit.cpp \
    financial.cpp \
    funcionario.cpp \
    gerente.cpp \
    main.cpp \
    mainwindow.cpp \
    operador.cpp \
    paymentsheet.cpp \
    presidente.cpp \
    signals.cpp

HEADERS += \
    data.h \
    diretor.h \
    edit.h \
    empresa.h \
    exihibition.h \
    finaledit.h \
    financial.h \
    funcionario.h \
    gerente.h \
    mainwindow.h \
    operador.h \
    paymentsheet.h \
    presidente.h \
    signals.h

FORMS += \
    edit.ui \
    exihibition.ui \
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
