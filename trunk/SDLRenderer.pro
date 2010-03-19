# QT -= core \
# gui
INCLUDEPATH += $$(HOME)/lib/SDL/include
INCLUDEPATH += $$(HOME)/lib/SDL/bin

# INCLUDEPATH += $$(HOME)/lib/Boost
LIBS += -lSDLmain
LIBS += -lpthread
LIBS += -L \
    $$(HOME)/lib/SDL/lib
LIBS += -lSDL
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
    ReflectableRay.h
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
    ReflectableRay.cpp
