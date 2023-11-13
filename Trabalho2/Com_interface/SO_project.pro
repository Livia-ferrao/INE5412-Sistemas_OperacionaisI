QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FIFO.cpp \
    LRU.cpp \
    OPT.cpp \
    main.cpp \
    mainwindow.cpp \
    memory.cpp \
    page.cpp

HEADERS += \
    FIFO.h \
    LRU.h \
    OPT.h \
    abstract_paging.h \
    mainwindow.h \
    memory.h \
    page.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    vsim-belady.txt \
    vsim-exemplo.txt \
    vsim-gcc.txt
