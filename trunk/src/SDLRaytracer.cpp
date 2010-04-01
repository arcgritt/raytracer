#include <ctime>
#include <string>

// Boost
#include "boost/random.hpp"

// SDL
#include "SDL/SDL.h"

// Project
#include "SDLRaytracer.h"

#include "Light.h"
#include "MaterialParser.h"
#include "RenderableObject.h"
#include "RIBParser.h"
#include "Triangle.h"


#ifdef WINDOWS
    // something weird with SDL causes this to screw up on Windows unless you have this line
    #undef main
#endif // #ifdef WINDOWS


/****** DEFINES ******/
#define DEBUG

// how many times the algorithm will recurse in order to calculate reflections
#define MAX_TRACE_DEPTH 5000
// depth of AA - (x*2)^2 samples (1 = 4 samples, 2 = 16 samples, 3 = 64 samples)
#define FULL_SCENE_ANTI_ALIASING_LEVEL 0

// arbitrary number which stops the surface from intersecting itself due to float rounding errors
// should be as SMALL as possible, until artifacts start occuring... 0.001 seems to do the trick
#define LAMBDA 0.001

#define PI 3.14159265358979323846264338327950288

unsigned int fsaaLevel = FULL_SCENE_ANTI_ALIASING_LEVEL;

#ifdef DEBUG

unsigned int m_rayIntersections = 0;
unsigned int m_recursiveBounces = 0;
unsigned int m_lightTraces = 0;

#endif // #ifdef DEBUG

//----------------------------------------------------------------------------------------------------------------------
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
        else if(strcmp(argv[argcount], "-aa") == 0)
        {
            fsaaLevel = Parser::ParseUnsignedInt(argv[++argcount]);
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


//----------------------------------------------------------------------------------------------------------------------
int SDLRaytracer::InitScene(std::string _materialsFile, std::string _ribFile)
{
    MaterialParser materialParser;
    std::vector<Material> materials = materialParser.ParseFile(_materialsFile);

    RIBParser ribParser;
    Scene scene = ribParser.ParseFile(_ribFile, materials);

    Material mat = scene.GetObjects()[0]->GetMaterial();

    /*scene.AddObject(new Triangle(
            Vector(0, 5, 30),
            Vector(-5, -10, 30),
            Vector(5, -10, 30),
            Colour(0,1,0),
            mat
            ));

    scene.AddObject(new Triangle(
            Vector(0, 5, 30),
            Vector(-5, -10, 30),
            Vector(-5, 5, 30),
            Colour(0,1,0),
            mat
            ));
    //*/

    const int start_time = clock();

    const unsigned int c_bpp = 32;

    SDL_Surface* backBuffer;

    if(!SDLRaytracer::SDLInit(backBuffer, scene.GetWidth(), scene.GetHeight(), c_bpp))
    {
        std::cerr << "SDL failed to initialise" << std::endl;
    }

    std::cout << "Dimensions: " << scene.GetWidth() << "x" << scene.GetHeight() << std::endl;

    const int frame_time = clock();

    SDLRaytracer::RaytraceScene(backBuffer, scene);

    const int finish_time = clock();


    printf("Total time: %3.2f seconds\n", difftime(finish_time, start_time)/CLOCKS_PER_SEC);
    printf("Render time: %3.2f seconds\n", difftime(finish_time, frame_time)/CLOCKS_PER_SEC);

#ifdef DEBUG
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
                        SDLRaytracer::RaytraceScene(backBuffer, scene);
                    }
                case SDLK_RIGHT:
                    {
                        SDLRaytracer::RaytraceScene(backBuffer, scene);
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



//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
void SDLRaytracer::RaytraceScene(SDL_Surface *&_backBuffer, Scene &_scene)
{
    Uint32 *_pixelBuffer = (Uint32 *)_backBuffer->pixels;

    const float c_aspectRatio = (float)_scene.GetWidth()/(float)_scene.GetHeight();
    const float c_halfWidth = c_aspectRatio*0.5;
    const float c_divisionSize = 1.0f/(float)_scene.GetHeight();

#ifdef DEBUG
    printf("Aspect ratio: %f\n", c_aspectRatio);
    printf("Y Axis Division Size: %f\n", c_divisionSize);
#endif // #ifdef DEBUG

    // number of samples in an orthagonal direction
    const unsigned int fsaaAxisSamples = pow(2, fsaaLevel); // * 2;

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
    for(unsigned int y=0; y<_scene.GetHeight(); y++)
    {
        for(unsigned int x=0; x<_scene.GetWidth(); x++)
        {
            float xPos = x*c_divisionSize-c_halfWidth;
            float yPos = y*c_divisionSize-0.5;            
            
            xPos -= offsetPosition;
            yPos -= offsetPosition;
            Colour pixelColour = SDLRaytracer::FSAARaytracePixel(_scene, xPos, yPos, fsaaSamples, fsaaAxisSamples, fsaaDivisionSize);

            unsigned int pixelColours[4];
            pixelColour.GetColour256(&pixelColours[0]);

            _pixelBuffer[x+y*_scene.GetWidth()] = SDL_MapRGB(_backBuffer->format, (Uint8)pixelColours[0], (Uint8)pixelColours[1], (Uint8)pixelColours[2]);
        }
        SDL_Flip(_backBuffer);
    }
}

//----------------------------------------------------------------------------------------------------------------------
Colour SDLRaytracer::FSAARaytracePixel(
                                       Scene &_scene,
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
                                          1) - _scene.GetCamera();
            // normalise it
            currDirection.Normalise();
            // save it to Ray object
            Ray cameraRay = Ray(currDirection);
            // trace it, with 0 trace depth because it is the camera/eye ray
            pixelColours[x*_fsaaAxisSamples + y] = RaytraceRay(_scene.GetAmbient(), _scene.GetObjects(), _scene.GetLights(), _scene.GetCamera(), cameraRay, 0);
        }
    }


    /*

    loop which multiplies samples back together to create average.
    from a design point of view, you could do _fsaaSamples minus 1 # of float adds, plus a float division

    for(unsigned int i = 1; i < _fsaaSamples; i++)
    {
        pixelColours[0] += pixelColours[i];
    }
    pixelColours[0] /= _fsaaSamples;

    OR _fsaaSamples minus 1 (e.g. 8+4+2+1) # of multiplications
    this loop uses the multiplication method, which also uses less memory

    */

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

//----------------------------------------------------------------------------------------------------------------------
Colour SDLRaytracer::RaytraceRay(float _ambient, std::vector<RenderableObject*>& _objects, std::vector<Light>& _lights, Vector &_rayOrigin, Ray &_ray, unsigned int _traceDepth)
{
#ifdef DEBUG
    m_rayIntersections++;
    if(_traceDepth > 0) m_recursiveBounces++;
#endif // #ifdef DEBUG
    bool hit = false;

    // for each object in scene
    for(unsigned int j=0; j<_objects.size();j++) {
        float distance = _objects[j]->DoIntersection(_rayOrigin, _ray.GetVector());

        // arbitrary number which stops the surface from intersecting itself due to float rounding errors
        // should be as SMALL as possible, until artifacts start occuring... 0.001 seems to do the trick
        if(distance >= LAMBDA) // if there is a hit
        {
            hit = true;
            _ray.Intersection(distance, _objects[j]);
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
        pixel_colour = CalculateColour(_ambient, _objects, _lights, pixel_fragment, _ray.GetVector());

        if(objectReflectivity == 0.0f || _traceDepth >= MAX_TRACE_DEPTH)
        {
            // If it's not reflective at all, we don't have to bother with recursion
            return pixel_colour;
        }
        // If it's TOTALLY reflective, we don't care about the colour of this object
        // If it's partially reflective, we need to multiply the colour of this object by its reflectants

        // calculate the reflection bounce ray
        Vector& rayVector = _ray.GetVector();
        Vector normal = pixel_fragment.GetNormal();
        const float dotRay_Normal = Vector::Dot(rayVector, normal);
        Vector reflectionVector = rayVector - (normal*2*dotRay_Normal);
        reflectionVector.Normalise();
        Ray reflectionray = Ray(reflectionVector);

        Vector origin = pixel_fragment.GetPosition();


        Colour reflection_colour = RaytraceRay(_ambient, _objects, _lights, origin, reflectionray, _traceDepth+1);
        reflection_colour *= objectReflectivity;
        pixel_colour *= (1.0f-objectReflectivity);
        pixel_colour += reflection_colour;
        return pixel_colour;
    }
    else // if it didn't hit anything
    {
        // background colour
        //return pixel_colour = Colour(0.1f, 0.1f, 0.1f);
        //return pixel_colour = Colour(0.2f, 0.2f, 0.2f);

        // SDL doesn't actually support alpha anyway...
        return pixel_colour = Colour(0.0f, 0.0f, 0.0f, 0.0f);
    }
}


//----------------------------------------------------------------------------------------------------------------------
Colour SDLRaytracer::CalculateColour(float _ambient, std::vector<RenderableObject*>& _objects, std::vector<Light>& _lights, Fragment &_fragment, Vector &_rayVector)
{
#ifdef DEBUG
    m_lightTraces++;
#endif // #ifdef DEBUG
    const Material mat = _fragment.GetMaterial();

    float diffuse_multiplier = 0;
    float specular_multiplier = 0;

    // for each light
    for(unsigned int l=0; l<_lights.size();l++)
    {
        Light& light = _lights[l];

        // point on object surface
        Vector surfacePoint = _fragment.GetPosition();

        // light center
        Vector lightPoint = light.GetPosition();

        // vector from point on surface to light
        Vector lightVector = lightPoint-surfacePoint;

        // save for attenuation because we will normalise it
        float lightSquareLength = lightVector.SquareLength();

        bool occluded = false;
        // SHADOWS: check against all objects
        for(unsigned int j=0; j<_objects.size(); j++)
        {
            float lightDistance = lightVector.SquareLength();

            lightVector.Normalise();
            float distance = _objects[j]->DoIntersection(surfacePoint, lightVector);

            if(distance >= LAMBDA && // if there is a hit
               distance < lightDistance) // if the object is between the light and the fragment
            {
                // set this external variable so we can skip light calculations
                occluded = true;
                // don't bother checking aganist other objects as there is already one in the way
                // if we were doing refraction it would not be this simple
                break;
            }
        }

        if(occluded) continue; // if there is a single object in the way, the light is occluded

        // Fragment normal
        Vector normal = _fragment.GetNormal();

        float diffuse = Vector::Dot(lightVector, normal);

        if(diffuse > 0.0f)
        {            
            //diffuse_multiplier += diffuse;

            float specular = 0;
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
                specular += phongIntensity;
            }

            /* Blinn */

            // half way between ray and light vectors
            Vector halfWayVector = lightVector + _rayVector;
            halfWayVector.Normalise();

            float blinn = Vector::Dot(halfWayVector, normal);

            if(blinn > 0.0f) // if dot product > 0 (angle less than 90)
            {
                float blinnIntensity = pow(blinn, exponent) * intensity;
                specular += blinnIntensity;
            }

            // Length = linear falloff... SquareLength = quadratic (real) falloff
            const float light_attenuation = lightSquareLength;
            float light_intensity = light.GetMagnitude()/light_attenuation;

            specular *= diffuse;
            specular_multiplier += specular*light_intensity;
            diffuse_multiplier += diffuse*light_intensity;
        }
    }

    Colour ambient = _fragment.GetColour(); //mat.GetDiffuseColour();
    ambient *= _ambient;

    Colour diffuse = _fragment.GetColour(); //mat.GetDiffuseColour();
    diffuse *= diffuse_multiplier;// * light_intensity;

    Colour specular = mat.GetSpecularColour();
    specular *= specular_multiplier;// * light_intensity;

    Colour finalColour = ambient + diffuse + specular;
    finalColour.Ceil();
    return finalColour;
}
