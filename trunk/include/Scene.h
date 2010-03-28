#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Vector.h"

#include "RenderableObject.h"
#include "Light.h"

class Scene
{
public:
    Scene();

    Scene(unsigned int _displayWidth, unsigned int _displayHeight, float _pixelAspectRatio, float _fieldOfView);

    Vector GetCamera() const { return m_camera; }

    unsigned int GetWidth() const { return m_displayWidth; }
    unsigned int GetHeight() const { return m_displayHeight; }

    /*unsigned int GetNumLights() const { return m_numLights; }
    const Light* GetLight(const unsigned int _lightID) const { return m_lights[_lightID]; }
    void SetLights(const unsigned int _numLights, Light** _lights);

    unsigned int GetNumObjects() const { return m_numObjects; }
    const RenderableObject* GetObject(const unsigned int _objectID) const { return m_objects[_objectID]; }
    void SetObjects(const unsigned int _numObjects, RenderableObject** _objects);*/

    void SetLights(std::vector<Light>& _lights) { m_lights = _lights; }
    std::vector<Light> GetLights() { return m_lights; }

    void SetObjects(std::vector<RenderableObject*>& _objects) { m_objects = _objects; }
    std::vector<RenderableObject*> GetObjects() { return m_objects; }

private:
    unsigned int m_displayWidth;
    unsigned int m_displayHeight;
    float m_pixelAspectRatio;
    float m_fieldOfView;
    Vector m_camera;

    std::vector<RenderableObject*> m_objects;

    std::vector<Light> m_lights;
    //unsigned int m_numObjects;
    //RenderableObject** m_objects;

    //unsigned int m_numLights;
    //Light** m_lights;

    void SetCamera(float _fieldOfView);
    void SetDimensions(unsigned int _displayWidth, unsigned int _displayHeight);

};

#endif // SCENE_H
