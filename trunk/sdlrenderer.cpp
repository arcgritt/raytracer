#include "sdlrenderer.h"
#include "SDL/SDL.h"

#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>

#include <cmath>
#include <float.h>
#include <ctime>
#include <algorithm>

#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"


#include "boost/random.hpp"
//#include "boost/thread.hpp"

#undef main

#define PI 3.1415926535

SDL_Surface *screen;	//This pointer will reference the backbuffer

float c_halfWidth;


const unsigned int c_num_spheres = 20;
const unsigned int c_num_lights = 1;

const unsigned int c_maxTraceDepth = 500;



RenderableObject* objects[c_num_spheres];
Light* lights[c_num_lights];



//boost::thread *t;



int main()//int argc, char *argv[])
{
    const int start_time = clock();

    #define RES_MULTI 1.25

    const unsigned int c_width = 1280*RES_MULTI;
    const unsigned int c_height = 720*RES_MULTI;
    const unsigned int c_bpp = 32;

    //c_width*=2;
    //c_height*=2;

    if(!SDLRenderer::SDLInit(c_width, c_height, c_bpp))
    {
        std::cerr << "SDL failed to initialise" << std::endl;
    }

    const unsigned int c_verticalFieldOfView = 60;
    Vector camera = SDLRenderer::CameraInit(c_verticalFieldOfView);


    const float c_aspectRatio = (float)c_width/(float)c_height;
    c_halfWidth = c_aspectRatio*0.5;
    // const int c_num_pixels = c_width*c_height;    // redundant?
    const float c_divisionSize = 1.0f/(float)c_height;


    const bool debug = true;
    if(debug) {
        //printf("Camera position: %f\n", c_cameraPosition);
        printf("Aspect ratio: %f\n", c_aspectRatio);
        printf("Y Axis Division Size: %f\n", c_divisionSize);
    }

    SDLRenderer::SceneInit();

    const int frame_time = clock();

    Uint32 *pixels = (Uint32 *)screen->pixels;

    // Draw the scene
    for(unsigned int y=0; y<c_height; y++)
    {
        for(unsigned int x=0; x<c_width; x++)
        {
            Colour pixelColour = SDLRenderer::RayTracePixel(camera, x, y, c_divisionSize);
            unsigned char pixelColours[4];
            pixelColour.getColour256(&pixelColours[0]);

            pixels[x+y*c_width] = SDL_MapRGB(screen->format, (Uint8)pixelColours[0], (Uint8)pixelColours[1], (Uint8)pixelColours[2]);
        }
    }

    const int finish_time = clock();

    printf("Render time: %3.2f seconds\n", difftime(finish_time, start_time)/CLOCKS_PER_SEC);
    printf("Draw time: %3.2f seconds\n", difftime(finish_time, frame_time)/CLOCKS_PER_SEC);

    // Update the screen
    SDL_Flip(screen);


    // pointer to pass to SDL_WaitEvent
    SDL_Event event;
    bool quit = false;
    while(quit == false)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            // all keyboard events
            case SDL_KEYDOWN:
                //int key = event.key.keysym.sym;
                switch (event.key.keysym.sym)
                {
                    // escape key = quit
                    case SDLK_ESCAPE:
                        quit = true;
                        //break;
                    // ALL keys
                    default:
                        std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                        break;
                }
                break;

            // close button
            case SDL_QUIT:
                quit = true;
                break;
        }
    }

    //Return success!
    return EXIT_SUCCESS;
}

bool SDLRenderer::SDLInit(const unsigned int _width, const unsigned int _height, const unsigned int _bpp)
{
    //We must first initialize the SDL video component, and check for success
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Set window title
    SDL_WM_SetCaption("Adam Gritt - RayTracer", "Adam Gritt - RayTracer");

    //When this program exits, SDL_Quit must be called
    atexit(SDL_Quit);

    //Set the video mode with double-buffering
    screen = SDL_SetVideoMode(_width, _height, _bpp, SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

Vector SDLRenderer::CameraInit(const unsigned int _verticalFieldOfView)
{
    const float c_cameraPosition = -0.5/tan((_verticalFieldOfView/2)*(PI/180));
    return Vector(0, 0, c_cameraPosition);
}

void SDLRenderer::SceneInit()
{
    // Random number generator
    boost::mt19937 Generator;


    boost::uniform_real<float> distributionPos(0.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

    boost::uniform_real<float> distribution(-1.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);

    for(unsigned int i=0; i<c_num_spheres;i++)
    {
        objects[i] = new Sphere(
                Vector(RandFloat()*9, RandFloat()*9, RandFloat()*5+30),
                RandPosFloat()*2+1,
                Material(
                        Colour(RandPosFloat(), RandPosFloat(), RandPosFloat()),
                        RandPosFloat()*0.1+0.3
                        )
                );
    }

    for(unsigned int i=0; i<c_num_lights;i++)
    {
        lights[i] = new Light(
                Vector(-7, RandFloat(), 30),
                0.5f,
                Material(
                        Colour(),
                        0.0f
                        ),
                3.0f
                );
    }
}


Colour SDLRenderer::RayTracePixel(Vector &_camera, const unsigned int _x, const unsigned int _y, const float _divisionSize)
{
    Vector currDirection = Vector(_x*_divisionSize-c_halfWidth,
                                  _y*_divisionSize-0.5,
                                  1) - _camera;
    currDirection.normalise();

    // Ray from camera to somewhere, rather than from an object to somewhere
    Ray cameraRay = Ray(currDirection);

    // Ray pixel_rays[x+y*c_width];
    // currPixel = Ray(currDirection);

    return RaytraceRay(_camera, cameraRay, 0);

}

Colour SDLRenderer::RaytraceRay(Vector &_rayOrigin, Ray &_ray, unsigned int _traceDepth)
{
    bool hit = false;

    // for each object in scene
    for(unsigned int j=0; j<c_num_spheres+c_num_lights;j++) {
        float distance = objects[j]->doIntersection(_rayOrigin, _ray.GetVector());

        // arbitrary number which stops the surface from intersecting itself due to float rounding errors
        // should be as SMALL as possible, until artifacts start occuring... 0.001 seems to do the trick
        const float lambda = 0.001;
        if(distance >= lambda) // if there is a hit
        {
            hit = true;
            _ray.Intersection(distance, *objects[j]);
        }
    }

    // if it hit something
    Colour pixel_colour;// = Colour(0.5f, 0.5f, 0.5f);
    if(hit)
    {
        // object that this pixel hits
        RenderableObject* objectIntersected = _ray.GetObjectIntersected();//.objects[currentPixel.GetObjectIntersected()];

        // surface normal, position and material of the point at which the pixel's ray hits the above object
        Fragment pixel_fragment = objectIntersected->getFragment(_rayOrigin, _ray.GetVector(), _ray.GetClosestIntersection());

        // its material
        Material objectMaterial = objectIntersected->getMaterial();
        float objectReflectivity = objectMaterial.GetReflectivity();


        // Get the intensity of light which is hitting this object
        float light_intensity = CalculateLighting(pixel_fragment);
        pixel_colour = CalculateColour(objectMaterial, light_intensity);

        if(objectReflectivity == 0.0f || _traceDepth >= c_maxTraceDepth)
        {
            // If it's not reflective at all, we don't have to bother with recursion
            return pixel_colour;
        }
        // If it's TOTALLY reflective, we don't care about the colour of this object
        // If it's partially reflective, we need to multiply the colour of this object by its reflectants

        // calculate the reflection bounce ray
        Vector rayVector = _ray.GetVector();
        Vector normal = pixel_fragment.GetNormal();
        Vector reflectionVector = rayVector - (normal*2*rayVector.dot(normal));
        //reflectionVector = reflectionVector;
        reflectionVector.normalise();
        //reflectionVector.printDebug();
        //reflectionVector = -reflectionVector;
        Ray reflectionray = Ray(reflectionVector);

        Vector origin = pixel_fragment.GetPosition();


        Colour reflection_colour = RaytraceRay(origin, reflectionray, _traceDepth+1);
        reflection_colour *= objectReflectivity;
        pixel_colour *= (1.0f-objectReflectivity);
        pixel_colour += reflection_colour;
        return pixel_colour;
    }
    else // if it didn't hit anything
    {
        // background colour
        return pixel_colour = Colour(0.1f, 0.1f, 0.1f);
    }
}


float SDLRenderer::CalculateLighting(Fragment& _fragment )
{
    float light_intensity = 0;
    // for each light
    for(unsigned int l=0; l<c_num_lights;l++)
    {
        Light* light = lights[l];

        // vector from intersection to light
        // could be used for light falloff
        Vector light_vector = light->getPosition()-_fragment.GetPosition();
        float light_attenuation = light_vector.SquareLength();

        light_vector.normalise();

        float dot_product = light_vector.dot(_fragment.GetNormal());
        //normal.dot()

        // if dot product > 0 (angle less than 90)
        if(dot_product > 0)
        {
            light_intensity += dot_product*(light->GetMagnitude()/sqrt(light_attenuation));
        }

    }

    // ambient light
    const float ambient_multiplier = 0.15;
    float ambient_modifier = (1.0f - light_intensity) * ambient_multiplier;
    light_intensity += ambient_modifier;
    //return light_intensity;

    return std::min(1.0f, light_intensity);
}


Colour SDLRenderer::CalculateColour(Material& _material, float _lightIntensity)
{
    // TODO: Pass fragment in so that normal pass is possible

    /* Normals
    light_intensity = 1;
    float r_base = fabs(normal.m_x);
    float g_base = fabs(normal.m_y);
    float b_base = fabs(normal.m_z);
    //*/

    ///* Lambert
    _lightIntensity = 1/_lightIntensity;
    float pixelColours[4];
    _material.GetColour().getColour(&pixelColours[0]);
    float r_base = pixelColours[0];
    float g_base = pixelColours[1];
    float b_base = pixelColours[2];
    float a = pixelColours[3];
    //*/

    /* Lambert Normals
    light_intensity = 1/light_intensity;
    float pixelColours[4];
    material_colour.getColour(&pixelColours[0]);
    float r_base = pixelColours[0] * fabs(normal.m_x);
    float g_base = pixelColours[1] * fabs(normal.m_y);
    float b_base = pixelColours[2] * fabs(normal.m_z);
    //*/


    float r = std::min(1.0f, (float)r_base/_lightIntensity);
    float g = std::min(1.0f, (float)g_base/_lightIntensity);
    float b = std::min(1.0f, (float)b_base/_lightIntensity);
    // alpha doesn't get modified by light

    return Colour(r, g, b, a);
}
