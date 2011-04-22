#-------------------------------------------------
#
# Project created by QtCreator 2011-04-21T19:54:47
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = rt

CONFIG += console

SOURCES += main.cpp\
    Scene.cpp \
    main_back.cpp \
    Sphere.cpp \
    Buffer.cpp \
    Material.cpp \
    PixelUtility.cpp \
    Eye.cpp \
    Light.cpp \
    GraphicsView.cpp \
    RTGraphicsScene.cpp \
    glee/GLee.c

HEADERS  += globals.h \
    Material.h \
    Scene.h \
    Eye.h \
    Sphere.h \
    Object.h \
    Buffer.h \
    Light.h \
    GraphicsView.h \
    PixelUtility.h \
    Unknown.h \
    RTGraphicsScene.h \
    glee/GLee.h \
    glee/GLee.h
