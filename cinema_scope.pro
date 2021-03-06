#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += debug_and_release

# TARGET = CinemaScope

# debug/release
CONFIG(release, debug|release) {
    DESTDIR = build/release
} else {
    DESTDIR = build/debug
}
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += console


SOURCES += \
        src/main.cpp \
        src/CinScopeWindow.cpp \
        src/CinDBReader.cpp \
        src/CinParamSliders.cpp \
        src/CinParameter.cpp \
        src/CinParamSet.cpp \
        src/CinDatabase.cpp \
        src/CinImageView.cpp \
        src/CinArtifactSet.cpp \
        src/CinDBView.cpp \
        src/CinCore.cpp \
        src/CinParameterMapDialog.cpp \
        src/CinCompoundSlider.cpp

HEADERS += \
        src/CinScopeWindow.h \
        src/CinDBReader.h \
        src/CinParamSliders.h \
        src/CinParameter.h \
        src/CinParamSet.h \
        src/CinDatabase.h \
        src/CinImageView.h \
        src/CinArtifactSet.h \
        src/CinDBView.h \
        src/CinCore.h \
        src/CinParameterMapDialog.h \
        src/CinCompoundSlider.h

