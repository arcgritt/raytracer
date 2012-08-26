#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Vector.h"

#include "Light.h"
#include "RenderableObject.h"

/// \file Scene.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Scene
/// \brief Encapsulates the objects which can be contained in a scene
/// \todo

class Scene
{

public:
  /// \brief The default constructor
  Scene();

  /// \brief Constructs a new scene and calculates the camera position
  /// @param[in] _displayWidth        the width of the scene, in pixels
  /// @param[in] _displayHeight       the height of the scene, in pixels
  /// @param[in] _pixelAspectRatio    the pixel aspect ratio of the scene
  /// @param[in] _fieldOfView         the vertical field of view of the scene
  Scene(
      const unsigned int _displayWidth,
      const unsigned int _displayHeight,
      const float _pixelAspectRatio,
      const float _fieldOfView
      );

  /// \brief Returns the scene's camera
  /// \returns the scene's camera
  Vector& GetCamera() { return m_camera; }

  /// \brief Returns the width, in pixels, of the scene to be rendered
  /// \returns the width, in pixels, of the scene to be rendered
  unsigned int GetWidth() const { return m_displayWidth; }

  /// \brief Returns the height, in pixels, of the scene to be rendered
  /// \returns the height, in pixels, of the scene to be rendered
  unsigned int GetHeight() const { return m_displayHeight; }

  /// \brief Adds a light to the scene
  /// @param[in] _light       the light to be added
  void AddLight(const Light& _light) { m_lights.push_back(_light); }

  /// \brief Sets the std::vector containg the scene's lights to the input value
  /// @param[in] _lights the std::vector containg the scene's lights
  void SetLights(const std::vector<Light> _lights) { m_lights = _lights; }

  /// \brief Returns an std::vector containing the scene's lights
  /// \returns an std::vector containing the scene's lights
  std::vector<Light>& GetLights() { return m_lights; }

  /// \brief Adds an object to the scene
  /// @param[in] _object      the object to be added
  void AddObject(RenderableObject* _object) { m_objects.push_back(_object); }

  /// \brief Sets the std::vector containg the scene's objects to the input value
  /// @param[in] _objects the std::vector containg the scene's objects
  void SetObjects(const std::vector<RenderableObject*> _objects) { m_objects = _objects; }

  /// \brief Returns an std::vector containing the scene's objects
  /// \returns an std::vector containing the scene's objects
  std::vector<RenderableObject*>& GetObjects() { return m_objects; }

  /// \brief Sets the ambient value to the input value
  /// @param[in] _ambient     the value to set the ambient to
  void SetAmbient(const float _ambient) { m_ambient = _ambient; }

  /// \brief Returns the intensity of ambient light in the scene
  /// \returns the intensity of ambient light in the scene
  float GetAmbient() const { return m_ambient; }
private:
  /// Width of the scene, in pixels
  unsigned int m_displayWidth;

  /// Height of the scene, in pixels
  unsigned int m_displayHeight;

  /// Pixel aspect ratio of the scene
  float m_pixelAspectRatio;

  /// Camera's vertical field of view
  float m_fieldOfView;

  /// Camera position
  Vector m_camera;

  /// Objects in the scene
  std::vector<RenderableObject*> m_objects;

  /// Lights in the scene
  std::vector<Light> m_lights;

  /// Ambient lighting multiplier in the scene
  float m_ambient;

private:
  /// \brief sets the position of the scene's camera based on the input field of view
  /// @param[in] _fieldOfView     the vertical field of view of the camera
  void SetCamera(const float _fieldOfView);

  /// \brief sets the dimension of the scene, in pixels
  /// @param[in] _displayWidth    the width of the scene, in pixels
  /// @param[in] _displayHeight   the height of the scene, in pixels
  void SetDimensions(const unsigned int _displayWidth, const unsigned int _displayHeight);

};

#endif // SCENE_H
