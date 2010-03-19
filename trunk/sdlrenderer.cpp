#include "sdlrenderer.h"
#include "SDL/SDL.h"

#include "unistd.h"
#include "stdlib.h"

#include "cmath"
#include "float.h"
#include "ctime"

#include "Colour.h"
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"


#include "boost/random.hpp"


const int start_time = clock();

Vector primaryRay;

const int c_width = 1280;
const int c_height = 720;
const int c_bpp = 32;

const int c_num_pixels = c_width*c_height;

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



    const int c_num_spheres = 50;
    RenderableObject* objects[c_num_spheres];



    /* create some 'random' spheres to draw */
    /*Sphere spheres[c_num_spheres];
    spheres[0] = Sphere(Vector(0,0,500), 100, Colour(0.1f, 0.5f, 0.9f));   // center, small, blue
    spheres[1] = Sphere(Vector(50,100,1000), 300, Colour(0.6f, 0.2f, 0.9f)); // purple
    spheres[2] = Sphere(Vector(-500,-100,500), 250, Colour(0.7f, 0.7f, 0.1f));    // left a bit and up a bit
    spheres[3] = Sphere(Vector(400,20,750), 400, Colour(0.9f, 0.5f, 0.4f));   // right a bit and far back
    spheres[4] = Sphere(Vector(100,600,-1000), 400, Colour(0.3f, 0.1f, 0.9f));    // up a lot, massive*/


    boost::mt19937 Generator;

    boost::uniform_real<float> distribLength(0.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distribLength);

    boost::uniform_real<float> distribLength2(-1.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribLength2);

    printf("Random float: %f", RandFloat());


    for(int i=0; i<c_num_spheres;i++)
    {
        objects[i] = new Sphere(Vector(RandFloat()*3000, RandFloat()*3000, RandPosFloat()*500+1000), RandPosFloat()*500, Colour(RandPosFloat(), RandPosFloat(), RandPosFloat()));
    }



    Sphere light = Sphere(Vector(100,100,500), 50);


    const int frame_time = clock();


    // Draw the scene
    Uint32 *pixels = (Uint32 *)screen->pixels;
    for(int i=0; i<c_num_pixels;i++)
    {

        bool hit = false;
        // pixel_ray = pixel_rays[i];
        for(int j=0; j<c_num_spheres;j++) {
            // RaySphereIntersect
            // source http://www.devmaster.net/wiki/Ray-sphere_intersection
            Vector dst = camera.getVector()-objects[j]->getPosition(); // distance from camera to sphere center

            float b = dst.dot(pixel_rays[i].getVector()); // angle between vector to sphere center and vector to pixel
            float c = dst.dot(dst) - objects[j]->getRadius()*objects[j]->getRadius(); // distance from camera to sphere center, squared
            float d = b*b - c;

            if(d >= 0) // if there is a hit
            {
                hit = true;
                float intersection_distance = -b - sqrt(d);
                pixel_rays[i].intersection(intersection_distance, j);
            }
        }


        Colour pixel_colour;
        if(hit)
        {
            pixel_colour = objects[pixel_rays[i].get_intersection_object()]->getMaterial().getColour();
            //pixel_colour = spheres[pixel_rays[i].get_intersection_object()].getColour();
        }
        else
        {
            // background colour
            pixel_colour = Colour(0.5f, 0.5f, 0.5f);
        }

        unsigned char pixelColours[4];
        pixel_colour.getColour256(&pixelColours[0]);

        pixels[i] = SDL_MapRGB(screen->format, (Uint8)pixelColours[0], (Uint8)pixelColours[1], (Uint8)pixelColours[2]);
    }


    /*// determine color at point of intersection
    pi = a_Ray.GetOrigin() + a_Ray.GetDirection() * a_Dist;
    // trace lights
    for ( int l = 0; l < m_Scene->GetNrPrimitives(); l++ )
    {
      Primitive* p = m_Scene->GetPrimitive( l );
      if (p->IsLight())
      {
        Primitive* light = p;
        // calculate diffuse shading

        vector3 L = ((Sphere*)light)->GetCentre() - pi;
        NORMALIZE( L );
        vector3 N = prim->GetNormal( pi );
        if (prim->GetMaterial()->GetDiffuse() > 0)
        {
          float dot = DOT( N, L );
          if (dot > 0)
          {
            float diff = dot * prim->GetMaterial()->GetDiffuse();
            // add diffuse component to ray color

            a_Acc += diff * prim->GetMaterial()->GetColor() * light->GetMaterial()->GetColor();
          }
        }
      }
    }*/




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
