TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG -= qt
CONFIG -= linux # qtcreator adds linux even if shouldn't, so we remove
QT       -= core
QT       -= gui


CONFIG += linux
#CONFIG += raspberry
#CONFIG += android
#CONFIG += win32
#CONFIG += playstation2
#CONFIG += dingux
#CONFIG += open_pandora
#CONFIG += wii
#CONFIG += dreamcast
#CONFIG += macosx



linux {
    TARGET = rescueblaster
    LIBS = -L/usr/X11R6/lib -lX11 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2_gfx `sdl2-config --libs` -ldl

    INCLUDES = -I/usr/include/SDL \
            -I/usr/include \
            -I. \
            -I./include \
            -L/usr/lib
    QMAKE_CCFLAGS += -DLINUX -DPC -Wno-reorder -Wno-ignored-qualifiers -fpermissive
    QMAKE_CXXFLAGS += -DLINUX -DPC -Wno-reorder -Wno-ignored-qualifiers -fpermissive
}

SOURCES += \
        main.cpp \
    graphics/graphlib.cpp \
    input/inputlib.cpp \
    playerlib.cpp \
    timerlib.cpp \
    fpscontrol.cpp \
    mediator.cpp

HEADERS += \
    graphics/graphlib.h \
    input/inputlib.h \
    defines.h \
    playerlib.h \
    timerlib.h \
    fpscontrol.h \
    file/file_map.h \
    file/file_map.h \
    defines.h \
    file/file_io.h \
    mediator.h \
    file/file_stage.h
