QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QLabelDragDrop/QLabelDragDrop.cpp \
    QPSD/private/list/list.c \
    QPSD/private/list/list_iterator.c \
    QPSD/private/list/list_node.c \
    QPSD/private/psd.c \
    QPSD/qtpsd.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QLabelDragDrop/QLabelDragDrop.h \
    QPSD/private/list/list.h \
    QPSD/private/psd.h \
    QPSD/private/psd_p.h \
    QPSD/qtpsd.h \
    QPSD/qtpsd_global.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
