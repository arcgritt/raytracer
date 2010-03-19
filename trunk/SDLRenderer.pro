INCLUDEPATH += $$(HOME)/lib/SDL/include
INCLUDEPATH += $$(HOME)/lib/SDL/bin
LIBS += -lSDLmain
LIBS += -L \
    $$(HOME)/lib/SDL/lib
LIBS += -lSDL
HEADERS += sdlrenderer.h \
    Box.h \
    Vector.h \
    Colour.h \
    Sphere.h \
    Ray.h
SOURCES += sdlrenderer.cpp \
    Box.cpp \
    Vector.cpp \
    Colour.cpp \
    Sphere.cpp \
    Ray.cpp
