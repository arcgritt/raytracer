INCLUDEPATH += $$(HOME)/lib/SDL/include
INCLUDEPATH += $$(HOME)/lib/SDL/bin
INCLUDEPATH += $$(HOME)/lib/Boost
LIBS += -lSDLmain
LIBS += -L \
    $$(HOME)/lib/SDL/lib
LIBS += -lSDL
HEADERS += sdlrenderer.h \
    Box.h \
    Vector.h \
    Colour.h \
    Sphere.h \
    Ray.h \
    Intersect.h \
    RenderableObject.h \
    Material.h
SOURCES += sdlrenderer.cpp \
    Box.cpp \
    Vector.cpp \
    Colour.cpp \
    Sphere.cpp \
    Ray.cpp \
    Intersect.cpp \
    RenderableObject.cpp \
    Material.cpp
