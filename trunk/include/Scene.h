#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Vector.h"

#include "RenderableObject.h"
#include "Light.h"

class Scene
{
public:
    /// \brief the default constructor
    Scene();

    /// \brief constructs a new scene and calculates the camera position
    /// @param[in] _displayWidth        the width of the scene, in pixels
    /// @param[in] _displayHeight       the height of the scene, in pixels
    /// @param[in] _pixelAspectRatio    the pixel aspect ratio of the scene
    /// @param[in] _fieldOfView         the vertical field of view of the scene
    Scene(unsigned int _displayWidth, unsigned int _displayHeight, float _pixelAspectRatio, float _fieldOfView);

    /// \brief
    /// \returns
    Vector& GetCamera() { return m_camera; }

    /// \brief returns the width, in pixels, of the scene to be rendered
    /// \returns the width, in pixels, of the scene to be rendered
    unsigned int GetWidth() const { return m_displayWidth; }

    /// \brief returns the height, in pixels, of the scene to be rendered
    /// \returns the height, in pixels, of the scene to be rendered
    unsigned int GetHeight() const { return m_displayHeight; }

    /// \brief adds a light to the scene
    /// @param[in] _light       the light to be added
    void AddLight(Light& _light) { m_lights.push_back(_light); }

    /// \brief sets the std::vector containg the scene's lights to the input value
    /// @param[in] _lights the std::vector containg the scene's lights
    void SetLights(std::vector<Light> _lights) { m_lights = _lights; }

    /// \brief returns an std::vector containing the scene's lights
    /// \returns an std::vector containing the scene's lights
    std::vector<Light>& GetLights() { return m_lights; }

    /// \brief adds an object to the scene
    /// @param[in] _object      the object to be added
    void AddObject(RenderableObject* _object) { m_objects.push_back(_object); }

    /// \brief sets the std::vector containg the scene's objects to the input value
    /// @param[in] _objects the std::vector containg the scene's objects
    void SetObjects(std::vector<RenderableObject*> _objects) { m_objects = _objects; }

    /// \brief returns an std::vector containing the scene's objects
    /// \returns an std::vector containing the scene's objects
    std::vector<RenderableObject*>& GetObjects() { return m_objects; }

private:
    /// the width of the scene, in pixels
    unsigned int m_displayWidth;

    /// the height of the scene, in pixels
    unsigned int m_displayHeight;

    /// the pixel aspect ratio of the scene
    float m_pixelAspectRatio;

    /// the camera's vertical field of view
    float m_fieldOfView;

    /// the camera
    Vector m_camera;

    /// the scene's objects
    std::vector<RenderableObject*> m_objects;

    /// the scene's lights
    std::vector<Light> m_lights;

    /// \brief sets the position of the scene's camera based on the input field of view
    /// @param[in] _fieldOfView     the vertical field of view of the camera
    void SetCamera(float _fieldOfView);

    /// \brief sets the dimension of the scene, in pixels
    /// @param[in] _displayWidth    the width of the scene, in pixels
    /// @param[in] _displayHeight   the height of the scene, in pixels
    void SetDimensions(unsigned int _displayWidth, unsigned int _displayHeight);

};

#endif // SCENE_H
