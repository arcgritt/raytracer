#include "sdlrenderer.h"
#include "SDL/SDL.h"

#include "unistd.h"
#include "stdlib.h"

#include "cmath"
#include "float.h"


#include "Colour.h"
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"


//Vector direction[]; // direction vectors for every pixel
Vector primaryRay;

const int c_width = 1280;
const int c_height = 720;
const int c_bpp = 32;

const int c_num_pixels = c_width*c_height;

//Vector direction[c_width*c_height];
Ray pixel_rays[c_num_pixels];

int main(int argc, char *argv[])
{
    SDL_Surface *screen;	//This pointer will reference the backbuffer

    //We must first initialize the SDL video component, and check for success
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    //When this program exits, SDL_Quit must be called
    atexit(SDL_Quit);

    //Set the video mode with double-buffering
    screen = SDL_SetVideoMode(c_width, c_height, c_bpp, SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }




    
    /* Create ray vector for every pixel */
    for(int y=0; y<c_height; y++)
    {
        for(int x=0; x<c_width; x++)
        {
            //Vector currDirection =
            //Vector &currDirection = direction[x+y*c_width];

            // field of view??
            int field_of_view = 255;

            Vector currDirection = Vector(x - (c_width/2), y - (c_height/2), field_of_view);
            currDirection.normalise();

            Ray &currPixel = pixel_rays[x+y*c_width];
            currPixel = Ray(currDirection);
        }
    }

    Ray camera = Ray(Vector(0,0,-800));





    /* create some 'random' spheres to draw */
    const int c_num_spheres = 5;
    Sphere spheres[c_num_spheres];

    spheres[0] = Sphere(Vector(0,0,500), 10);   // center, small
    spheres[1] = Sphere(Vector(50,100,1000),300);
    spheres[2] = Sphere(Vector(-500,-100,500), 250);    // left a bit and up a bit
    spheres[3] = Sphere(Vector(400,20,750), 400);   // right a bit and far back
    spheres[4] = Sphere(Vector(100,600,-1000), 400);    // up a lot, massive

    for(int i=0; i<c_num_pixels;i++)
    {
       // pixel_ray = pixel_rays[i];
        for(int j=0; j<c_num_spheres;j++) {
            // RaySphereIntersect
            // source http://www.devmaster.net/wiki/Ray-sphere_intersection
            Vector dst = camera.getVector()-spheres[j].getCenter(); // distance from camera to sphere center

            float b = dst.dot(pixel_rays[i].getVector()); // angle between vector to sphere center and vector to pixel
            float c = dst.dot(dst) - spheres[j].getRadius()*spheres[j].getRadius(); // distance from camera to sphere center, squared
            float d = b*b - c;

            if(d > 0)
            {
                pixel_rays[i].intersection(-b - sqrt(d));
            }
        }
    }


    /* Draw the scene */
    Uint32 *pixels = (Uint32 *)screen->pixels;
    for(int pixel_num=0;pixel_num<c_num_pixels;pixel_num++)
    {
        Colour pixel;
        if(pixel_rays[pixel_num].get_closest_intersection() < FLT_MAX)
        {
            pixel = Colour(0.5f, 0.0f, 0.0f);
        }
        else
        {
            pixel = Colour(0.5f, 0.5f, 0.5f);
        }
        unsigned char pixelColours[4];
        pixel.getColour256(&pixelColours[0]);

        pixels[pixel_num] = SDL_MapRGB(screen->format, (Uint8)pixelColours[0], (Uint8)pixelColours[1], (Uint8)pixelColours[2]);
    }

    // Update the screen
    SDL_Flip(screen);

    //Wait for 2500ms (2.5 seconds) so we can see the image
    SDL_Delay(2500);

    //Return success!
    return EXIT_SUCCESS;
}
