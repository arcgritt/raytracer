QT -= core \
    gui
LIBS += -lSDL
LIBS += -lSDLmain
CONFIG += thread
LIBS += -lpthread
DESTDIR = bin
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
HEADERS += sdlrenderer.h \
    Box.h \
    Vector.h \
    Colour.h \
    Sphere.h \
    Ray.h \
    RenderableObject.h \
    Material.h \
    Fragment.h \
    Light.h \
    ReflectableRay.h \
    Plane.h
SOURCES += sdlrenderer.cpp \
    Box.cpp \
    Vector.cpp \
    Colour.cpp \
    Sphere.cpp \
    Ray.cpp \
    RenderableObject.cpp \
    Material.cpp \
    Fragment.cpp \
    Light.cpp \
    ReflectableRay.cpp \
    Plane.cpp
#for(headerfile, HEADERS):exists($$headerfile) { 
#    HEADERS -= $$headerfile
#    HEADERS += include/$$headerfile
#}
#for(sourcefile, SOURCES):exists($$sourcefile) { 
#    SOURCES -= $$sourcefile
#    SOURCES += src/$$sourcefile
#}
