#-------------------------------------------------
#
# Project created by QtCreator 2019-07-07T16:24:10
#
#-------------------------------------------------

QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp\
    aerosolpage.cpp \
    atmosadddialog.cpp \
    cloudpage.cpp \
    imagedialog.cpp \
    inputconfshow.cpp \
        mainwindow.cpp \
    generalpage.cpp \
    atmospherepage.cpp \
    commonfunction.cpp \
    multidialog.cpp \
    plotcurve.cpp \
    singledialog.cpp \
    transmodelpage.cpp \
    waitdialog.cpp

HEADERS  += mainwindow.h \
    aerosolpage.h \
    atmosadddialog.h \
    cloudpage.h \
    generalpage.h \
    atmospherepage.h \
    commonfunction.h \
    imagedialog.h \
    inputconfshow.h \
    multidialog.h \
    plotcurve.h \
    singledialog.h \
    transmodelpage.h \
    waitdialog.h

FORMS    += mainwindow.ui \
    aerosolpage.ui \
    atmosadddialog.ui \
    cloudpage.ui \
    generalpage.ui \
    atmospherepage.ui \
    imagedialog.ui \
    inputconfshow.ui \
    multidialog.ui \
    singledialog.ui \
    transmodelpage.ui \
    waitdialog.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH +=D:\work_software\language\include
LIBS += -LD:\work_software\language\libs\ -lpython27

DISTFILES += \
    process_qt_input.py
CONFIG += c++11

RESOURCES += \
    title_logo.qrc
