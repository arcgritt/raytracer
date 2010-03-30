#include "Scene.h"


#include <cmath>

#define PI 3.14159265358979323846264338327950288

Scene::Scene()
{
}

Scene::Scene(unsigned int _displayWidth, unsigned int _displayHeight, float _pixelAspectRatio, float _fieldOfView)
{
    SetDimensions(_displayWidth, _displayHeight);
    m_pixelAspectRatio = _pixelAspectRatio; // does nothing ATM
    SetCamera(_fieldOfView);
}

void Scene::SetCamera(float _fieldOfView)
{
    const float c_cameraPosition = -0.5/tan((_fieldOfView/2)*(PI/180));
    m_camera = Vector(0, 0, c_cameraPosition);
}

void Scene::SetDimensions(unsigned int _displayWidth, unsigned int _displayHeight)
{
    m_displayWidth = _displayWidth;
    m_displayHeight = _displayHeight;
}

/*void Scene::SetLights(unsigned int _numLights, Light**_lights)
{
    m_numLights = _numLights;
    m_lights = _lights;
}

void Scene::SetObjects(unsigned int _numObjects, RenderableObject**_objects)
{
    m_numObjects = _numObjects;
    m_objects = _objects;
}*/
