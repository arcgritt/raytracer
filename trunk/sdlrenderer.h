#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include "Colour.h"

class SDLRenderer
{
public:
    SDLRenderer();
    Colour RayTracePixel(const int _x, const int _y);
private:
};

#endif // SDLRENDERER_H
