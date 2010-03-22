# Don't need these Qt libraries which are added by default
QT -= core \
    gui
DESTDIR = bin
OBJECTS_DIR = obj
RCC_DIR = resources

#SUBDIRS += src include

HEADERS_DIR = include
SOURCES_DIR = src

# SDL
LIBS += -lSDL
LIBS += -lSDLmain

# Qt threading library
CONFIG += thread
LIBS += -lpthread
unix: { 
    INCLUDEPATH += $$(HOME)/lib/SDL/include
    INCLUDEPATH += $$(HOME)/lib/SDL/bin
    LIBS += -L \
        $$(HOME)/lib/SDL/lib
}

# INCLUDEPATH += $$(HOME)/lib/Boost
win32: { 
    INCLUDEPATH += C:\lib\SDL-1.2.14\include
    INCLUDEPATH += C:\lib\SDL-1.2.14\bin
    INCLUDEPATH += C:\lib\boost_1_42_0
    LIBS += -L \
        C:\lib\SDL-1.2.14\lib
    CONFIG += console
}

HEADERS += $$HEADERS_DIR/sdlrenderer.h \
    $$HEADERS_DIR/Box.h \
    $$HEADERS_DIR/Vector.h \
    $$HEADERS_DIR/Colour.h \
    $$HEADERS_DIR/Sphere.h \
    $$HEADERS_DIR/Ray.h \
    $$HEADERS_DIR/RenderableObject.h \
    $$HEADERS_DIR/Material.h \
    $$HEADERS_DIR/Fragment.h \
    $$HEADERS_DIR/Light.h \
    $$HEADERS_DIR/ReflectableRay.h \
    $$HEADERS_DIR/Plane.h

 #for(file, HEADERS) {
 #   HEADERS -= $$file
 #   HEADERS += include/$$file
# }


SOURCES += $$SOURCES_DIR/sdlrenderer.cpp \
    $$SOURCES_DIR/Box.cpp \
    $$SOURCES_DIR/Vector.cpp \
    $$SOURCES_DIR/Colour.cpp \
    $$SOURCES_DIR/Sphere.cpp \
    $$SOURCES_DIR/Ray.cpp \
    $$SOURCES_DIR/RenderableObject.cpp \
    $$SOURCES_DIR/Material.cpp \
    $$SOURCES_DIR/Fragment.cpp \
    $$SOURCES_DIR/Light.cpp \
    $$SOURCES_DIR/ReflectableRay.cpp \
    $$SOURCES_DIR/Plane.cpp
