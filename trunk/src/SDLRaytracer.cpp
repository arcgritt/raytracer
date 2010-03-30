#ifdef WINDOWS

#include <ctime>
#include <string>

#endif // #ifdef WINDOWS

// Boost
#include "boost/random.hpp"
//#include "boost/thread.hpp"

// SDL
#include "SDL/SDL.h"

// Project
#include "SDLRaytracer.h"
#include "MaterialParser.h"
#include "RIBParser.h"
#include "Light.h"
#include "RenderableObject.h"

#ifdef WINDOWS
// something weird with SDL causes this to screw up on Windows unless you have this line
#undef main
#endif // #ifdef WINDOWS



/****** DEFINES ******/
#define DEBUG true


// TODO: Set this up in the RIB file
#define NUM_LIGHTS 1
// how many times the algorithm will recurse in order to calculate reflections
#define MAX_TRACE_DEPTH 5
// depth of AA - (x*2)^2 samples (1 = 4 samples, 2 = 16 samples, 3 = 64 samples)
#define FULL_SCENE_ANTI_ALIASING_LEVEL 0

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
Light* lights[NUM_LIGHTS];
std::vector<RenderableObject*> m_objects;

int main(int argc, char *argv[])//int argc, char *argv[])
{
    int argcount=1; /* argv 1 is the first parameter */

    std::string materialsFile;
    std::string ribFile;

    while(argcount < argc )
    {
        if(strcmp(argv[argcount],"-r") == 0)
        {
            ribFile = argv[++argcount];
            argcount++;
        }
        else if(strcmp(argv[argcount],"-m") == 0)
        {
            materialsFile = argv[++argcount];
            argcount++;
        }
        else
        {
            std::cout << "unknown argument #" << argcount++ << std::endl;
        }
    }

    bool exit = false;
    if(materialsFile.empty())
    {
        exit = true;
        std::cout << "Materials file not specified" << std::endl;
    }

    if(ribFile.empty())
    {
        exit = true;
        std::cout << "RIB file not specified" << std::endl;
    }

    if(exit)
    {
        std::cout << "Usage: -r \"foo.rib\", -m \"bar\"" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Using materials file: " << materialsFile << std::endl;
    std::cout << "Using RIB file: " << ribFile << std::endl << std::endl;

    return SDLRaytracer::InitScene(materialsFile, ribFile);
}


int SDLRaytracer::InitScene(std::string _materialsFile, std::string _ribFile)
{
    MaterialParser materialParser;
    std::vector<Material> materials = materialParser.ParseFile(_materialsFile);

    RIBParser ribParser;
    Scene scene = ribParser.ParseFile(_ribFile, materials);

    m_objects = scene.GetObjects();

    const int start_time = clock();

    const unsigned int c_bpp = 32;

    SDL_Surface* backBuffer;

    if(!SDLRaytracer::SDLInit(backBuffer, scene.GetWidth(), scene.GetHeight(), c_bpp))
    {
        std::cerr << "SDL failed to initialise" << std::endl;
    }

    std::cout << "Width: " << scene.GetWidth() << std::endl;
    std::cout << "Height: " << scene.GetHeight() << std::endl;


    for(unsigned int i=0; i<NUM_LIGHTS;i++)
    {
        Material mat = Material(Colour(), 0.0f);

        lights[i] = new Light(
                Vector(-7, 0, 15),
                0.5f,
                mat,
                10.0f
                );
    }


    const int frame_time = clock();

    SDLRaytracer::RenderScene(backBuffer, scene);

    const int finish_time = clock();

#ifdef DEBUG
    printf("Render time: %3.2f seconds\n", difftime(finish_time, start_time)/CLOCKS_PER_SEC);
    printf("Draw time: %3.2f seconds\n", difftime(finish_time, frame_time)/CLOCKS_PER_SEC);

    std::cout << "Ray Traces: " << m_rayIntersections << std::endl;
    std::cout << "Recursive Traces: " << m_recursiveBounces << std::endl;
    std::cout << "Light Traces: " << m_lightTraces << std::endl;
#endif // DEBUG


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
                        continue;
                    }
                case SDLK_LEFT:
                    {
                        SDLRaytracer::RenderScene(backBuffer, scene);
                    }
                case SDLK_RIGHT:
                    {
                        SDLRaytracer::RenderScene(backBuffer, scene);
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


void SDLRaytracer::RenderScene(SDL_Surface *&_backBuffer, Scene &_scene) {
    // utility function which takes 2 variables instead of 4
    RaytraceScene(_backBuffer, _scene.GetWidth(), _scene.GetHeight(), _scene.GetCamera());
}

void SDLRaytracer::RaytraceScene(SDL_Surface *&_backBuffer, const unsigned int _width, const unsigned int _height, Vector &_camera)
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

    // Draw the scene
    for(unsigned int y=0; y<_height; y++)
    {
        for(unsigned int x=0; x<_width; x++)
        {
            float xPos = x*c_divisionSize-c_halfWidth;
            float yPos = y*c_divisionSize-0.5;            
            
            xPos -= offsetPosition;
            yPos -= offsetPosition;
            Colour pixelColour = SDLRaytracer::FSAARaytracePixel(_camera, xPos, yPos, fsaaSamples, fsaaAxisSamples, fsaaDivisionSize);

            unsigned int pixelColours[4];
            pixelColour.GetColour256(&pixelColours[0]);

            _pixelBuffer[x+y*_width] = SDL_MapRGB(_backBuffer->format, (Uint8)pixelColours[0], (Uint8)pixelColours[1], (Uint8)pixelColours[2]);
        }
        SDL_Flip(_backBuffer);
    }
}

Colour SDLRaytracer::FSAARaytracePixel(Vector &_camera,
                                       const float _xPos,
                                       const float _yPos,
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

    /*for(unsigned int i = 1; i < _fsaaSamples; i++)
    {

        pixelColours[0] += pixelColours[i];
    }

    pixelColours[0] /= _fsaaSamples;*/

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
    for(unsigned int j=0; j<m_objects.size();j++) {
        float distance = m_objects[j]->DoIntersection(_rayOrigin, _ray.GetVector());

        // arbitrary number which stops the surface from intersecting itself due to float rounding errors
        // should be as SMALL as possible, until artifacts start occuring... 0.001 seems to do the trick
        if(distance >= LAMBDA) // if there is a hit
        {
            hit = true;
            _ray.Intersection(distance, m_objects[j]);
        }
    }

    // if it hit something
    Colour pixel_colour;
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
        pixel_colour = CalculateColour(pixel_fragment, _ray.GetVector());

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
        return pixel_colour = Colour(0.1f, 0.1f, 0.1f);
        //return pixel_colour = Colour(0.2f, 0.2f, 0.2f);
    }
}


Colour SDLRaytracer::CalculateColour(Fragment &_fragment, Vector &_rayVector)
{
#ifdef DEBUG
    m_lightTraces++;
#endif // #ifdef DEBUG
    const Material mat = _fragment.GetMaterial();

    float light_intensity = 0;

    const float ambient_multiplier = 0.15;
    float diffuse_multiplier = 0;
    float specular_multiplier = 0;
    // for each light
    for(unsigned int l=0; l<NUM_LIGHTS;l++)
    {
        Light* light = lights[l];

        // point on object surface
        Vector surfacePoint = _fragment.GetPosition();

        // light center
        Vector lightPoint = light->GetPosition();

        // vector from point on surface to light
        Vector lightVector = lightPoint-surfacePoint;

        bool occluded = false;
        // check against all objects including lights
        for(unsigned int j=0; j<m_objects.size()+NUM_LIGHTS;j++)
        {
            // don't check against this light as it will always intersect
            if(j != m_objects.size() + l)
            {

                float lightDistance = lightVector.SquareLength();

                float distance = m_objects[j]->DoIntersection(surfacePoint, lightVector);

                // 'hard' shadows
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

        if(occluded) break; // if there is a single object in the way, the light is occluded


        //float unattenuatedIntensity = 0;

        // Fragment normal
        Vector normal = _fragment.GetNormal();



        Vector lightVectorNormalised = lightVector;
        lightVectorNormalised.Normalise();

        diffuse_multiplier = std::max(0.0f, Vector::Dot(lightVectorNormalised, normal));


        if(diffuse_multiplier > 0.0f)
        {            
            float exponent = mat.GetSpecularExponent();
            float intensity = mat.GetSpecularIntensity();

            /* Phong */

            // reflection of lightVector over object normal
            Vector reflectionVector = -lightVector + normal * Vector::Dot(normal, lightVector) * 2;
            reflectionVector.Normalise();

            // dot product of light reflection and ray, for Phong calculations
            float phong = Vector::Dot(reflectionVector, -_rayVector);


            if(phong > 0.0f) // if dot product > 0 (angle less than 90)
            {
                float phongIntensity = pow(phong, exponent) * intensity;
                specular_multiplier += phongIntensity;
            }

            /* Blinn */

            // half way between ray and light vectors
            Vector halfWayVector = lightVector + _rayVector;
            halfWayVector.Normalise();

            float blinn = Vector::Dot(halfWayVector, normal);

            if(blinn > 0.0f) // if dot product > 0 (angle less than 90)
            {
                float blinnIntensity = pow(blinn, exponent) * intensity;
                specular_multiplier += blinnIntensity;
            }


            specular_multiplier *= diffuse_multiplier;
        }

        if(diffuse_multiplier > 0)   // don't waste time with attenuation if it's got no light, ~5% speed boost
        {
            // Length = linear falloff... SquareLength = quadratic (real) falloff
            const float light_attenuation = lightVector.SquareLength();
            light_intensity += 1/light_attenuation*light->GetMagnitude()*10;
        }
    }

    Colour ambient = mat.GetDiffuseColour();
    ambient *= ambient_multiplier;


    Colour diffuse = mat.GetDiffuseColour();
    diffuse *= diffuse_multiplier * light_intensity;

    Colour specular = mat.GetSpecularColour();
    specular *= specular_multiplier * light_intensity;

    Colour finalColour = ambient + diffuse + specular;
    finalColour.Ceil();
    finalColour.Floor();

    return finalColour;
}
