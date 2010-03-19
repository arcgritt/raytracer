#include "sdlrenderer.h"
#include "SDL/SDL.h"

#include <unistd.h>
#include <stdlib.h>

#include <cmath>
#include <float.h>
#include <ctime>
#include <algorithm>

#include "Colour.h"
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"


#include "boost/random.hpp"
//#include <boost/thread/thread.hpp>

#define PI 3.1415926535

const int start_time = clock();

const int c_verticalFieldOfView = 120;
const int c_width = 1280;
const int c_height = 720;
const int c_bpp = 32;


const float c_aspectRatio = (float)c_width/(float)c_height;
const float c_halfWidth = c_aspectRatio*0.5;
const int c_num_pixels = c_width*c_height;
const float c_yDivisionSize = 1.0f/(float)c_height;

const int c_num_spheres = 50;
const int c_num_lights = 1;
RenderableObject* objects[c_num_spheres+c_num_lights];

Vector camera;

//Ray pixel_rays[c_num_pixels];

int main(int argc, char *argv[])
{
    SDL_Surface *screen;	//This pointer will reference the backbuffer

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
    screen = SDL_SetVideoMode(c_width, c_height, c_bpp, SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    const float c_cameraPosition = -0.5/tan((c_verticalFieldOfView/2)*(PI/180));
    camera = Vector(0, 0, c_cameraPosition);

    const bool debug = true;




    if(debug) {
        printf("Camera position: %f\n", c_cameraPosition);
        printf("Aspect ratio: %f\n", c_aspectRatio);
        printf("Y Axis Division Size: %f\n", c_yDivisionSize);
    }

    // Random number generator
    boost::mt19937 Generator;

    boost::uniform_real<float> distributionPos(0.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

    boost::uniform_real<float> distribution(-1.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);



    //printf("Random float: %f", RandFloat());


    for(int i=0; i<c_num_spheres;i++)
    {
        objects[i] = new Sphere(
                Vector(RandFloat()*10, RandFloat()*10, RandPosFloat()+30),
                RandPosFloat(),
                Colour(RandPosFloat(), RandPosFloat(), RandPosFloat())
                );
    }

    for(int i=0; i<c_num_lights;i++)
    {
        objects[i+c_num_spheres] = new Sphere(
                Vector(-50, RandFloat(), 30),
                1,
                Colour()
                );
    }

    const int frame_time = clock();

    Uint32 *pixels = (Uint32 *)screen->pixels;

    // Draw the scene
    for(int y=0; y<c_height; y++)
    {
        for(int x=0; x<c_width; x++)
        {
            Colour pixelColour = RayTracePixel(x, y);
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

    //Wait for 2500ms (2.5 seconds) so we can see the image
    SDL_Delay(2500);

    //Return success!
    return EXIT_SUCCESS;
}


Colour SDLRenderer::RayTracePixel(const int _x, const int _y)
{
    Ray currentPixel;
    Fragment pixel_fragment;
    Vector currDirection = Vector(_x*c_yDivisionSize-c_halfWidth,
                                  _y*c_yDivisionSize-0.5,
                                  1) - camera;

    currDirection.normalise();

    currentPixel = Ray(currDirection);

    // Ray pixel_rays[x+y*c_width];
    // currPixel = Ray(currDirection);


    bool hit = false;

    // for each object in scene
    for(int j=0; j<c_num_spheres+c_num_lights;j++) {
        float distance = objects[j]->doIntersection(camera, currentPixel.getVector());

        if(distance >= 0) // if there is a hit
        {
            hit = true;
            currentPixel.intersection(distance, j);
        }
    }


    Colour pixel_colour;
    if(hit)
    {
        // object that this pixel hits
        RenderableObject* intersected_object = objects[currentPixel.get_intersection_object()];

        // surface normal, position and material of the point at which the pixel's ray hits the above object
        Fragment pixel_fragment = intersected_object->getFragment(camera, currentPixel.getVector(), currentPixel.get_closest_intersection());

        // its material
        Colour material_colour = intersected_object->getMaterial().getColour();

        // its normal
        Vector normal = pixel_fragment.getNormal();

        float light_intensity = 0;
        // for each light
        for(int l=0; l<c_num_lights;l++)
        {
            RenderableObject* light = objects[l+c_num_spheres];

            // vector from intersection to light
            // could be used for light falloff
            Vector light_vector = light->getPosition()-pixel_fragment.getPosition();

            light_vector.normalise();

            float dot_product = light_vector.dot(normal);
            //normal.dot()

            // if dot product > 0 (angle less than 90)
            if(dot_product > 0)
            {
                light_intensity += dot_product;
            }

        }        

        ///* Normals
        light_intensity = 1;
        float r_base = fabs(normal.m_x);
        float g_base = fabs(normal.m_y);
        float b_base = fabs(normal.m_z);
        //*/

        /* Lambert
        light_intensity = 1/light_intensity;
        float pixelColours[4];
        material_colour.getColour(&pixelColours[0]);
        float r_base = pixelColours[0];
        float g_base = pixelColours[1];
        float b_base = pixelColours[2];
        */

        float r = std::min(1.0f, (float)r_base/light_intensity);
        float g = std::min(1.0f, (float)g_base/light_intensity);
        float b = std::min(1.0f, (float)b_base/light_intensity);

        return pixel_colour = Colour(r, g, b);


        //pixel_colour = spheres[pixel_rays[i].get_intersection_object()].getColour();
    }
    else
    {
        // background colour
        return pixel_colour = Colour(0.5f, 0.5f, 0.5f);
    }

}
