#ifndef SDLRAYTRACER_H
#define SDLRAYTRACER_H

// SDL
#include "SDL/SDL.h"

#include <vector>

#include "Colour.h"
#include "Scene.h"
#include "Vector.h"
#include "Ray.h"


class SDLRaytracer
{
public:
    /// \brief the default constructor
    SDLRaytracer();

    /// \brief generates the objects from input file and calls appropriate functions
    /// @param[in] _materialsFile
    /// @param[in] _ribFile
    /// \returns EXIT_SUCCESS if the scene was initialised successfully or EXIT_FAILURE if there was an error (e.g. the scene information files could not be read)
    static int InitScene(std::string _materialsFile, std::string _ribFile);


    /// \brief initialises the SDL window
    /// @param[in] _backBuffer      a pointer to the backbuffer to be used for drawing to the screen
    /// @param[in] _width           the width of the screen, in pixels
    /// @param[in] _height          the height of the screen, in pixels
    /// @param[in] _bpp             the number of bits per pixel, hardcoded to 32-bit
    /// \returns boolean value representing whether or not SDL was initialised successfully
    static bool SDLInit(SDL_Surface*& _backBuffer, const unsigned int _width, const unsigned int _height, const unsigned int _bpp);

    /// \brief utility function which calls Raytracescene with approrriate stuff
    /// @param[in] _backBuffer      a pointer to the backbuffer to be used for drawing to the screen
    /// @param[in] _scene           an data storage object containing the scene's camera, objects and lights
    static void RenderScene(SDL_Surface*& _backBuffer, Scene& scene);

    /// \brief calculates the distance between FSAA samples and calls FSAARayTracePixel for each pixel in the scene, passing this information. After each line of the scene is rendered, the backbuffer is blitted to the screen
    /// @param[in] _backBuffer      a pointer to the backbuffer to be used for drawing to the screen
    /// @param[in] _width           the width of the screen, in pixels
    /// @param[in] _height          the height of the screen, in pixels
    /// @param[in] _camera          the scene's camera
    static void RaytraceScene(SDL_Surface*& _backBuffer, const unsigned int _width, const unsigned int _height, Vector& _camera);

    /// \brief calculates the colour of a pixel, by tracing the required number of samples for FSAA and then averaging them
    /// @param[in] _camera              the scene's camera
    /// @param[in] _xPos                the x coordinate of the pixel
    /// @param[in] _yPos                the y coordinate of the pixel
    /// @param[in] _fsaaSamples         the total number of anti-aliasing samples
    /// @param[in] _fsaaAxisSamples     the number of anti-aliasing samples on each axis (equal to sqrt(_fsaaSamples))
    /// @param[in] _fsaaDivisionSize    the distance between each ray along each axis
    /// \returns the final colour of the specified pixel
    static Colour FSAARaytracePixel(Vector& _camera,
                                    const float _xPos,
                                    const float _yPos,
                                    unsigned int _fsaaSamples,
                                    const unsigned int _fsaaAxisSamples,
                                    const float _fsaaDivisionSize);

    /// \brief calculates the colour of a sample, specified by a ray. The trace depth specifies the maximum number of reflections which the ray will trace to. Recursively multiplies with it's own return value to calculate the colour of reflections.
    /// @param[in] _rayOrigin           the point where the ray originated from
    /// @param[in] _ray                 the (normalised) direction of the ray
    /// @param[in] _traceDepth          the maximum level of recursion for reflections
    /// \returns the colour of the sample
    static Colour RaytraceRay(Vector& _rayOrigin, Ray& _ray, unsigned int _traceDepth);

    /// \brief calculates the colour of a sample, based upon the object which was intersected and the ray vector
    /// @param[in] _fragment            a container object, holding the material, colour, surface normal and point at which the object was intersected
    /// @param[in] _rayVector
    /// \returns the colour of the fragment
    static Colour CalculateColour(Fragment& _fragment, Vector& _rayVector);
private:

};

#endif // SDLRAYTRACER_H
