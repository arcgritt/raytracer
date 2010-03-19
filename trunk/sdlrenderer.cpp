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


const int start_time = clock();

Vector primaryRay;

const int c_verticalFieldOfView = 120;

const int c_width = 1280;
const int c_height = 720;

const float c_aspectRatio = c_width/c_height;

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



    //float const c_cameraPosition = (c_width/2)/tan(c_field_of_view/2);

    //printf("aspect ratio: %f\n", c_aspectRatio/2);


    //float const c_cameraPositionTest = (c_aspectRatio/2)/tan(c_field_of_view/2);

    float const c_cameraPositionTest = tan(c_verticalFieldOfView/2);

    printf("Camera position should be: %f\n", c_cameraPositionTest);

    Vector camera = Vector(0, 0, -2000);
    
    /* Create ray vector for every pixel */
    for(int y=0; y<c_height; y++)
    {
        float const c_halfWidth = c_aspectRatio/2;
        float const c_xDivisionSize = c_aspectRatio/c_width;
        float const c_yDivisionSize = 1/c_height;


        for(int x=0; x<c_width; x++)
        {
            //Vector currDirection =
            //Vector &currDirection = direction[x+y*c_width];

            // field of view??
            //int field_of_view = 0;

            Vector currDirection = Vector(x - (c_width/2), (c_height/2) - y, 0) - camera;
            //Vector currDirection = Vector((x*c_xDivisionSize) - c_halfWidth,
                                         // (y*c_yDivisionSize) - 0.5,
                                     //     0) - camera;
            currDirection.normalise();
            //currDirection.printDebug();

            Ray &currPixel = pixel_rays[x+y*c_width];
            currPixel = Ray(currDirection);
        }
    }

    
    
    // Random number generator
    boost::mt19937 Generator;

    boost::uniform_real<float> distributionPos(0.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandPosFloat(Generator, distributionPos);

    boost::uniform_real<float> distribution(-1.0f, 1.0f);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > RandFloat(Generator, distribution);


    const int c_num_spheres = 50;
    const int c_num_lights = 1;
    RenderableObject* objects[c_num_spheres+c_num_lights];

   //printf("Random float: %f", RandFloat());


    for(int i=0; i<c_num_spheres;i++)
    {
        objects[i] = new Sphere(
                        Vector(RandFloat()*300, RandFloat()*300, RandPosFloat()*50+1000),
                        RandPosFloat()*50,
                        Colour(RandPosFloat(), RandPosFloat(), RandPosFloat())
                        );
    }

    for(int i=0; i<c_num_lights;i++)
    {
        objects[i+c_num_spheres] = new Sphere(
                        Vector(-500, RandFloat()*300, 500),
                        10,
                        Colour()
                                    );
    }


    //Sphere light = Sphere(Vector(100,100,500), 50);


    const int frame_time = clock();


    // Draw the scene
    Uint32 *pixels = (Uint32 *)screen->pixels;
    
    
    Fragment pixel_fragment;

    // for each pixel
    for(int i=0; i<c_num_pixels;i++)
    {

        bool hit = false;
        // pixel_ray = pixel_rays[i];

        // for each object in scene
        for(int j=0; j<c_num_spheres+c_num_lights;j++) {
            /*// RaySphereIntersect
            // source http://www.devmaster.net/wiki/Ray-sphere_intersection
            Vector dst = camera.getVector()-objects[j]->getPosition(); // distance from camera to sphere center

            float b = dst.dot(pixel_rays[i].getVector()); // angle between vector to sphere center and vector to pixel
            float c = dst.dot(dst) - objects[j]->getRadius()*objects[j]->getRadius(); // distance from camera to sphere center, squared
            float d = b*b - c;*/

            float distance = objects[j]->doIntersection(camera, pixel_rays[i].getVector());
            
            if(distance >= 0) // if there is a hit
            {
                hit = true;
                //float intersection_distance = -b - sqrt(d);
                pixel_rays[i].intersection(distance, j);
            }
        }


        Colour pixel_colour;
        if(hit)
        {
            // object that this pixel hits
            RenderableObject* intersected_object = objects[pixel_rays[i].get_intersection_object()];

            // surface normal and position of the point at which the pixel's ray hits the above object
            Fragment pixel_fragment = intersected_object->getFragment(camera, pixel_rays[i].getVector(), pixel_rays[i].get_closest_intersection());

            // its material
            Colour material_colour = intersected_object->getMaterial().getColour();

            // its normal
            Vector normal = pixel_fragment.getNormal();


            float light_intensity = 0;
            
            for(int l=0; l<c_num_lights;l++)
            {
                RenderableObject* light = objects[l+c_num_spheres];
                Vector light_vector = light->getPosition()-pixel_fragment.getPosition();//intersected_object->getPosition();
                light_vector.normalise();
                float dot_product = light_vector.dot(normal);
                //normal.dot()

                if(dot_product > 0)
                {
                    light_intensity += dot_product;
                }

            }

            /*
            // normal pass comp with material colour
            float pixelColours[4];
            material_colour.getColour(&pixelColours[0]);
            pixel_colour = Colour(fabs(normal.m_x)*pixelColours[0], fabs(normal.m_y)*pixelColours[1], fabs(normal.m_z)*pixelColours[2]);
            */


            // normal pass
            light_intensity = 1/light_intensity;
            //light_intensity = 1;


            //Normals
            /*float r_base = fabs(normal.m_x);
            float g_base = fabs(normal.m_y);
            float b_base = fabs(normal.m_z);*/


            float pixelColours[4];
            material_colour.getColour(&pixelColours[0]);
            float r_base = pixelColours[0];
            float g_base = pixelColours[1];
            float b_base = pixelColours[2];

            

            float r = std::min(1.0f, (float)r_base/light_intensity);
            float g = std::min(1.0f, (float)g_base/light_intensity);
            float b = std::min(1.0f, (float)b_base/light_intensity);

            pixel_colour = Colour(r, g, b);


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
