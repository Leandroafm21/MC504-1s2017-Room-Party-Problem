TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    graphics.c \
    actions.c \
    threads.c

HEADERS += \
    graphics.h \
    actions.h \
    threads.h
