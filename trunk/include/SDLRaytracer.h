#ifndef SDLRAYTRACER_H
#define SDLRAYTRACER_H

// SDL
#include "SDL/SDL.h"

#include "Colour.h"
#include "Vector.h"
#include "Ray.h"


class SDLRaytracer
{
public:
    SDLRaytracer();
    static bool SDLInit(const unsigned int _width, const unsigned int _height, const unsigned int _bpp);
    static Vector CameraInit();
    static void SceneObjectsInit();

    static void RenderScene(const unsigned int _width, const unsigned int _height);
    static void RaytraceScene(Uint32* pixelBuffer, const unsigned int _width, const unsigned int _height, Vector& _camera);

    static Colour RaytracePixel(Vector& _camera, float _xPos, float _yPos);
    static Colour FSAAPixel(Vector& _camera, const unsigned int _x, const unsigned int _y, const float _divisionSize, const float _halfWidth);
    static Colour FSAARaytracePixel(Vector& _camera,
                                    float _xPos,
                                    float _yPos,
                                    unsigned int _fsaaSamples,
                                    const unsigned int _fsaaAxisSamples,
                                    const float _fsaaDivisionSize);

    static Colour RaytraceRay(Vector& _rayOrigin, Ray& ray, unsigned int _traceDepth);

    static float CalculateLighting(Fragment& _fragment);
    static Colour CalculateColour(Material& _material, float _lightIntensity);
private:

};

#endif // SDLRAYTRACER_H
