#ifndef SDLRAYTRACER_H
#define SDLRAYTRACER_H

// SDL
#include "SDL/SDL.h"

#include <vector>

#include "Material.h"
#include "Colour.h"
#include "Vector.h"
#include "Ray.h"


class SDLRaytracer
{
public:
    SDLRaytracer();

    static int RayTrace(std::string _materialsFile, std::string _ribFile);


    static bool SDLInit(SDL_Surface*& _backBuffer, const unsigned int _width, const unsigned int _height, const unsigned int _bpp);


    static Vector CameraInit();

    static void SceneObjectsInit(std::vector<Material> _materials);


    static void RenderScene(SDL_Surface*& _backBuffer, const unsigned int _width, const unsigned int _height);

    static void RaytraceScene(SDL_Surface*& _backBuffer, const unsigned int _width, const unsigned int _height, Vector& _camera);

    static Colour RaytracePixel(Vector& _camera, float _xPos, float _yPos);

    static Colour FSAAPixel(Vector& _camera, const unsigned int _x, const unsigned int _y, const float _divisionSize, const float _halfWidth);

    static Colour FSAARaytracePixel(Vector& _camera,
                                    float _xPos,
                                    float _yPos,
                                    unsigned int _fsaaSamples,
                                    const unsigned int _fsaaAxisSamples,
                                    const float _fsaaDivisionSize);

    static Colour RaytraceRay(Vector& _rayOrigin, Ray& ray, unsigned int _traceDepth);

    //static float CalculateLighting(Fragment& _fragment, Vector& _rayVector);

    //static Colour CalculateColour(Material& _material, float _lightIntensity);

    static Colour CalculateColour(Fragment& _fragment, Vector& _rayVector, Material& _material);
private:

};

#endif // SDLRAYTRACER_H
