#include "Scene.h"

#include <cmath>

#define PI 3.14159265358979323846264338327950288

//----------------------------------------------------------------------------------------------------------------------
Scene::Scene()
{

}

//----------------------------------------------------------------------------------------------------------------------
Scene::Scene(const unsigned int _displayWidth, const unsigned int _displayHeight, const float _pixelAspectRatio, const float _fieldOfView)
{
  SetDimensions(_displayWidth, _displayHeight);
  m_pixelAspectRatio = _pixelAspectRatio; // does nothing ATM
  SetCamera(_fieldOfView);
  m_ambient = 0;
}

//----------------------------------------------------------------------------------------------------------------------
void Scene::SetCamera(const float _fieldOfView)
{
  const float c_cameraPosition = -0.5/tan((_fieldOfView/2)*(PI/180));
  m_camera = Vector(0, 0, c_cameraPosition);
}

//----------------------------------------------------------------------------------------------------------------------
void Scene::SetDimensions(const unsigned int _displayWidth, const unsigned int _displayHeight)
{
  m_displayWidth = _displayWidth;
  m_displayHeight = _displayHeight;
}
