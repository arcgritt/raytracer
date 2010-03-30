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

    void AddLight(Light& _light) { m_lights.push_back(_light); }
    
    void SetLights(std::vector<Light> _lights) { m_lights = _lights; }
    std::vector<Light>& GetLights() { return m_lights; }

    void AddObject(RenderableObject* _object) { m_objects.push_back(_object); }
    
    void SetObjects(std::vector<RenderableObject*> _objects) { m_objects = _objects; }
    std::vector<RenderableObject*>& GetObjects() { return m_objects; }

private:
    unsigned int m_displayWidth;
    unsigned int m_displayHeight;
    float m_pixelAspectRatio;
    float m_fieldOfView;
    Vector m_camera;

    std::vector<RenderableObject*> m_objects;

    std::vector<Light> m_lights;

    void SetCamera(float _fieldOfView);
    void SetDimensions(unsigned int _displayWidth, unsigned int _displayHeight);

};

#endif // SCENE_H
