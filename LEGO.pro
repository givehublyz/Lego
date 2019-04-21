#-------------------------------------------------
#
# Project created by QtCreator 2019-04-14T20:52:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LEGO
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    design/designcomwidget.cpp \
    design/designglwidget.cpp \
    design/designopwidget.cpp \
    design/designwidget.cpp \
    edit/editwidget.cpp \
    component/component.cpp \
    component/simpleroundedcomponent.cpp \
    component/vertexposdatafactory.cpp \
    common/mesh.cpp \
    common/buffer.cpp \
    common/shader.cpp \
    common/camera.cpp \
    common/light.cpp \
    common/material.cpp \
    common/transform.cpp

HEADERS += \
        mainwindow.h \
    mainwindow.h \
    design/designcomwidget.h \
    design/designglwidget.h \
    design/designopwidget.h \
    design/designwidget.h \
    edit/editwidget.h \
    component/component.h \
    component/simpleroundedcomponent.h \
    component/vertexposdatafactory.h \
    common/mesh.h \
    common/buffer.h \
    common/shader.h \
    common/camera.h \
    common/light.h \
    common/material.h \
    common/transform.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
