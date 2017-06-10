#-------------------------------------------------
#
# Project created by QtCreator 2017-05-21T16:05:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shepherding_model
TEMPLATE = app


SOURCES += main.cpp\
        main_window.cpp \
    general_params.cpp \
    agent_params.cpp \
    shepherd_params.cpp \
    visual_window.cpp \
    model/shepherd.cpp \
    model/agent.cpp \
    model/algorithm.cpp \
    model/abstract_object.cpp \
    model/mobile_object.cpp \
    model/other_object.cpp \
    other_objects_params.cpp \
    experiment.cpp

HEADERS  += main_window.h \
    general_params.h \
    agent_params.h \
    shepherd_params.h \
    visual_window.h \
    model/shepherd.h \
    model/agent.h \
    model/algorithm.h \
    model/abstract_object.h \
    model/mobile_object.h \
    model/other_object.h \
    other_objects_params.h \
    experiment.h

FORMS    += main_window.ui \
    general_params.ui \
    agent_params.ui \
    shepherd_params.ui \
    visual_window.ui \
    other_objects_params.ui

RESOURCES += \
    resourses.qrc
