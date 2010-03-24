#ifdef WINDOWS

#include <ctime>

#endif // #ifdef WINDOWS

// Boost
#include "boost/random.hpp"
//#include "boost/thread.hpp"

// SDL
#include "SDL/SDL.h"

// Project
#include "SDLRaytracer.h"
#include "Sphere.h"
#include "Light.h"

// something weird with SDL causes this to screw up on Windows unless you have this line
#undef main


// DEFINES

#define DEBUG true

// numbers of each type of object (randomly generated)
#define NUM_SPHERES 20
#define NUM_LIGHTS 1

// use this to change the resolution by a multiple (rather than mess with pixel numbers)
#define RESOLUTION_MULTIPLIER 1
#define PIXELS_WIDE 1280
#define PIXELS_HIGH 720

// how many times the algorithm will recurse in order to calculate reflections
#define MAX_TRACE_DEPTH 5
// depth of AA - (x*2)^2 samples (1 = 4 samples, 2 = 16 samples, 3 = 64 samples)
#define FULL_SCENE_ANTI_ALIASING_LEVEL 2

// Vertical field of view of camera. Human eye is 120. Max is 180/aspect ratio
#define FIELD_OF_VIEW 60

// arbitrary number which stops the surface from intersecting itself due to float rounding errors
// should be as SMALL as possible, until artifacts start occuring... 0.001 seems to do the trick
#define LAMBDA 0.001


#define PI 3.14159265358979323846264338327950288


#ifdef DEBUG

unsigned int m_rayIntersections = 0;
unsigned int m_recursiveBounces = 0;
unsigned int m_lightTraces = 0;

#endif // #ifdef DEBUG

// TODO: Make a Scene class which contains all these
RenderableObject* objects[NUM_SPHERES];
Light* lights[NUM_LIGHTS];

int main(void)//int argc, char *argv[])
{
    const int start_time = clock();

    const unsigned int c_width = PIXELS_WIDE*RESOLUTION_MULTIPLIER;
    const unsigned int c_height = PIXELS_HIGH*RESOLUTION_MULTIPLIER;
    const unsigned int c_bpp = 32;

    SDL_Surface* backBuffer;

    if(!SDLRaytracer::SDLInit(backBuffer, c_width, c_height, c_bpp))
    {
        std::cerr << "SDL failed to initialise" << std::endl;
    }

    const int frame_time = clock();

    SDLRaytracer::RenderScene(backBuffer, c_width, c_height);

    const int finish_time = clock();



#ifdef DEBUG
    printf("Render time: %3.2f seconds\n", difftime(finish_time, start_time)/CLOCKS_PER_SEC);
    printf("Draw time: %3.2f seconds\n", difftime(finish_time, frame_time)/CLOCKS_PER_SEC);

    std::cout << "Ray Traces: " << m_rayIntersections << std::endl;
    std::cout << "Recursive Traces: " << m_recursiveBounces << std::endl;
    std::cout << "Light Traces: " << m_lightTraces << std::endl;
#endif // DEBUG

    // Update the screen
    SDL_Flip(backBuffer);


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
            {
                //int key = event.key.keysym.sym;
                switch (event.key.keysym.sym)
                {
                    // escape key = quit
                    case SDLK_ESCAPE:
                    {
                        quit = true;
                        //break;
                    // ALL keys
                    }
                    default:
                    {
                        std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                        break;
                    }
                }
                break;
            }

            // close button
            case SDL_QUIT:
            {
                quit = true;
                break;
            }
        }
    }

    //Return success!
    return EXIT_SUCCESS;
}

bool SDLRaytracer::SDLInit(SDL_Surface *&_backBuffer, const unsigned int _width, const unsigned int _height, const unsigned int _bpp)
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
    _backBuffer = SDL_SetVideoMode(_width, _height, _bpp, SDL_DOUBLEBUF);
    if (_backBuffer == NULL) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

Vector SDLRaytracer::CameraInit()
{
    const float c_cameraPosition = -0.5/tan((FIELD_OF_VIEW/2)*(PI/180));
    return Vector(0, 0, c_cameraPosition);
}

void SDLRaytracer::SceneObjectsInit()
{
    // Random number generator
    boost::mt19937 Generator;


    boost::uniform_real<float> distributionPos(0.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

    boost::uniform_real<float> distribution(-1.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);

    for(unsigned int i=0; i<NUM_SPHERES;i++)
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

    for(unsigned int i=0; i<NUM_LIGHTS;i++)
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

void SDLRaytracer::RenderScene(SDL_Surface *&_backBuffer, unsigned int _width, unsigned int _height) {
    SDLRaytracer::SceneObjectsInit();

    Vector camera = SDLRaytracer::CameraInit();

    RaytraceScene(_backBuffer, _width, _height, camera);
}

void SDLRaytracer::RaytraceScene(SDL_Surface *&_backBuffer, unsigned int _width, unsigned int _height, Vector &_camera)
{
    Uint32 *_pixelBuffer = (Uint32 *)_backBuffer->pixels;

    const float c_aspectRatio = (float)_width/(float)_height;
    const float c_halfWidth = c_aspectRatio*0.5;
    const float c_divisionSize = 1.0f/(float)_height;

    if(DEBUG) {
        //printf("Camera position: %f\n", c_cameraPosition);
        printf("Aspect ratio: %f\n", c_aspectRatio);
        printf("Y Axis Division Size: %f\n", c_divisionSize);
    }

#ifdef FULL_SCENE_ANTI_ALIASING_LEVEL

    // number of samples in an orthagonal direction
    const unsigned int fsaaAxisSamples = pow(2, FULL_SCENE_ANTI_ALIASING_LEVEL); // * 2;
    //std::cout << fsaaAxisSamples << std::endl;
    // total number of samples
    unsigned int fsaaSamples = fsaaAxisSamples * fsaaAxisSamples;

    // half pixel size
    const float halfDivisionSize = c_divisionSize*0.5;
    // distance between fsaa samples
    const float fsaaDivisionSize = c_divisionSize/fsaaAxisSamples;
    // half distance between fsaa samples
    const float halfFSAADivisionSize = fsaaDivisionSize*0.5;

    // calculate offset so we can use a clean loop for calculing sample positions
    const float offsetPosition = halfDivisionSize - halfFSAADivisionSize;

#endif // FULL_SCENE_ANTI_ALIASING_LEVEL

    // Draw the scene
    for(unsigned int y=0; y<_height; y++)
    {
        for(unsigned int x=0; x<_width; x++)
        {
            float xPos = x*c_divisionSize-c_halfWidth;
            float yPos = y*c_divisionSize-0.5;            
            
#ifdef FULL_SCENE_ANTI_ALIASING_LEVEL

            xPos -= offsetPosition;
            yPos -= offsetPosition;
            Colour pixelColour = SDLRaytracer::FSAARaytracePixel(_camera, xPos, yPos, fsaaSamples, fsaaAxisSamples, fsaaDivisionSize);

#endif // #ifdef FULL_SCENE_ANTI_ALIASING_LEVEL

#ifndef FULL_SCENE_ANTI_ALIASING_LEVEL

            Colour pixelColour = SDLRaytracer::RaytracePixel(_camera, xPos, yPos);

#endif // #ifndef FULL_SCENE_ANTI_ALIASING_LEVEL

            /*if(FULL_SCENE_ANTI_ALIASING_LEVEL > 0) {
                pixelColour
            }
            else
            {

            }*/
            unsigned int pixelColours[4];
            pixelColour.GetColour256(&pixelColours[0]);

            _pixelBuffer[x+y*_width] = SDL_MapRGB(_backBuffer->format, (Uint8)pixelColours[0], (Uint8)pixelColours[1], (Uint8)pixelColours[2]);
        }
        SDL_Flip(_backBuffer);
    }
}


Colour SDLRaytracer::RaytracePixel(Vector &_camera, float _xPos, float _yPos)
{
    Vector currDirection = Vector(_xPos,
                                  _yPos,
                                  1) - _camera;
    currDirection.Normalise();

    // Ray from camera to somewhere, rather than from an object to somewhere
    Ray cameraRay = Ray(currDirection);

    return RaytraceRay(_camera, cameraRay, 0);
}

Colour SDLRaytracer::FSAARaytracePixel(Vector &_camera,
                                       float _xPos,
                                       float _yPos,
                                       unsigned int _fsaaSamples,
                                       const unsigned int _fsaaAxisSamples,
                                       const float _fsaaDivisionSize)
{
    // array to store each pixel sample
    Colour pixelColours[_fsaaSamples];
    for(unsigned int x = 0; x < _fsaaAxisSamples; x++)
    {
        for(unsigned int y = 0; y < _fsaaAxisSamples; y++)
        {
            // for each sample
            // slightly modified vector
            Vector currDirection = Vector(_xPos + (x*_fsaaDivisionSize),
                                          _yPos + (y*_fsaaDivisionSize),
                                          1) - _camera;
            // normalise it
            currDirection.Normalise();
            // save it to Ray object
            Ray cameraRay = Ray(currDirection);
            // trace it
            pixelColours[x*_fsaaAxisSamples + y] = RaytraceRay(_camera, cameraRay, 0);
        }
    }

    // TODO: static function in colour class, which takes an array of colours and averages them

    // loop which multiplies samples back together to create average.
    // from a design point of view, you could do _fsaaSamples minus 1 # of float adds, plus a float division
    // OR _fsaaSamples minus 1 (e.g. 8+4+2+1) # of multiplications
    // this loop uses the multiplication method, which also uses less memory

    // _fsaaSamples is divided by 2 every loop iteration,
    // leading to 8, then 4, then 2, then 1 multiplications - if you had 16 samples
    while(_fsaaSamples > 1)
    {
        // iteration is used so that the output is placed into the first bunch of array positions (e.g. 0-7)
        // this is used because i is incremented by 2 every loop iteration
        unsigned int iteration = 0;
        for(unsigned int i = 0; i < _fsaaSamples; i=i+2)
        {
            // on first loop, 0 becomes the average of [0, 1], 1 becomes [2,3] etc
            pixelColours[iteration] &= pixelColours[i+1];
            iteration++;
        }
        // bit shift right _fsaaSamples (e.g. 16 becomes 8)
        _fsaaSamples /= 2;
    }

    // return the first element of the array, which should have ended up with the average of all of the array
    return pixelColours[0];
}

Colour SDLRaytracer::RaytraceRay(Vector &_rayOrigin, Ray &_ray, unsigned int _traceDepth)
{
#ifdef DEBUG
    m_rayIntersections++;
    if(_traceDepth > 0) m_recursiveBounces++;
#endif // #ifdef DEBUG
    bool hit = false;

    // for each object in scene
    for(unsigned int j=0; j<NUM_SPHERES+NUM_LIGHTS;j++) {
        float distance = objects[j]->DoIntersection(_rayOrigin, _ray.GetVector());

        // arbitrary number which stops the surface from intersecting itself due to float rounding errors
        // should be as SMALL as possible, until artifacts start occuring... 0.001 seems to do the trick
        if(distance >= LAMBDA) // if there is a hit
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
        Fragment pixel_fragment = objectIntersected->GetFragment(_rayOrigin, _ray.GetVector(), _ray.GetClosestIntersection());

        // its material
        Material objectMaterial = objectIntersected->GetMaterial();
        float objectReflectivity = objectMaterial.GetReflectivity();


        // Get the intensity of light which is hitting this object
        float light_intensity = CalculateLighting(pixel_fragment);
        pixel_colour = CalculateColour(objectMaterial, light_intensity);

        if(objectReflectivity == 0.0f || _traceDepth >= MAX_TRACE_DEPTH)
        {
            // If it's not reflective at all, we don't have to bother with recursion
            return pixel_colour;
        }
        // If it's TOTALLY reflective, we don't care about the colour of this object
        // If it's partially reflective, we need to multiply the colour of this object by its reflectants

        // calculate the reflection bounce ray
        Vector rayVector = _ray.GetVector();
        Vector normal = pixel_fragment.GetNormal();
        const float dotRay_Normal = Vector::Dot(rayVector, normal);
        Vector reflectionVector = rayVector - (normal*2*dotRay_Normal);
        reflectionVector.Normalise();
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
        //return pixel_colour = Colour(1.0f, 1.0f, 1.0f);
        return pixel_colour = Colour(0.1f, 0.1f, 0.1f);
        //return pixel_colour = Colour(0.2f, 0.2f, 0.2f);
    }
}


float SDLRaytracer::CalculateLighting(Fragment& _fragment )
{
#ifdef DEBUG
    m_lightTraces++;
#endif // #ifdef DEBUG

    float light_intensity = 0;
    // for each light
    for(unsigned int l=0; l<NUM_LIGHTS;l++)
    {
        Light* light = lights[l];
        Vector light_vector = light->GetPosition()-_fragment.GetPosition();
        float lightDistance = light_vector.SquareLength();

        bool occluded = false;
        // check against all objects including lights
        for(unsigned int j=0; j<NUM_SPHERES+NUM_LIGHTS;j++) {
            // don't check against this light as it will always intersect
            if(j != NUM_SPHERES + l) {
                Vector surfacePoint = _fragment.GetPosition();
                float distance = objects[j]->DoIntersection(surfacePoint, light_vector);

                if(distance >= LAMBDA && // if there is a hit
                   distance < lightDistance) // if the object is between the light and the fragment
                {
                    // set this external variable so we can skip light calculations
                    occluded = true;
                    // don't bother checking aganist other objects as there is already one in the way
                    // if we were doing refraction it would not be this simple
                    break;
                    //hit = true;
                    //_ray.Intersection(distance, *objects[j]);
                }
            }
        }

        if(occluded) break; //

        // vector from intersection to light
        // could be used for light falloff
        const float light_attenuation = light_vector.Length(); // Length = linear falloff... SquareLength = quadratic (real) falloff

        light_vector.Normalise();
        const float dotLight_Normal = Vector::Dot(light_vector, _fragment.GetNormal());
        //float dot_product = light_vector.dot(_fragment.GetNormal());
        //normal.dot()

        // if dot product > 0 (angle less than 90)
        if(dotLight_Normal > 0)
        {
            light_intensity += dotLight_Normal*(light->GetMagnitude()/sqrt(light_attenuation));
        }

    }

    // ambient light
    const float ambient_multiplier = 0.15;
    float ambient_modifier = (1.0f - light_intensity) * ambient_multiplier;
    light_intensity += ambient_modifier;
    //return light_intensity;

    return std::min(1.0f, light_intensity);
}


Colour SDLRaytracer::CalculateColour(Material& _material, float _lightIntensity)
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
    _material.GetColour().GetColour(&pixelColours[0]);
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
