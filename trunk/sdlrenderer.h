#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include "Colour.h"
#include "Vector.h"
#include "Ray.h"


class SDLRenderer
{
public:
    SDLRenderer();
    static Colour RayTracePixel(Vector& _camera, const unsigned int _x, const unsigned int _y, const float _divisionSize, const float _halfWidth);
    static bool SDLInit(const unsigned int _width, const unsigned int _height, const unsigned int _bpp);
    static Vector CameraInit(const unsigned int _fieldOfView);
    static void SceneInit();
    static Colour RaytraceRay(Vector& _rayOrigin, Ray& ray, unsigned int _traceDepth);

    static float CalculateLighting(Fragment& _fragment);
    static Colour CalculateColour(Material& _material, float _lightIntensity);
private:

};

#endif // SDLRENDERER_H
