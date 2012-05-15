#include "BlackDragonEngine/Camera.h"

namespace BlackDragonEngine
{
static inline float clamp(float x, float a, float b)
{
  return x < a ? a : (x > b ? b : x);
}

void Camera::ForcePosition(Vector2 const& position)
{
  _position = position;
}

void Camera::SetPosition(Vector2 const& position)
{
  _position = Vector2(
        clamp(position.x, _worldRectangle.left,
              _worldRectangle.width - GetViewPortWidth()),
        clamp(position.y, _worldRectangle.top,
              _worldRectangle.height - GetViewPortHeight()));
}

Camera::Vector2 const& Camera::GetPosition()
{
  return _position;
}

void Camera::SetWorldRectangle(Rectangle const& worldRectangle)
{
  _worldRectangle = worldRectangle;
}

Camera::Rectangle const& Camera::GetWorldRectangle()
{
  return _worldRectangle;
}

void Camera::SetViewPortWidth(float width)
{
  _viewPortSize.x = width;
}

int Camera::GetViewPortWidth()
{
  return (int)_viewPortSize.x;
}

void Camera::SetViewPortHeight(float height)
{
  _viewPortSize.y = height;
}

int Camera::GetViewPortHeight()
{
  return (int)_viewPortSize.y;
}

Camera::Rectangle Camera::GetViewPort()
{
  return Rectangle((int)_position.x, (int)_position.y, GetViewPortWidth(),
                 GetViewPortHeight());
}

void Camera::Move(Vector2 const& offset)
{
  _position += offset;
}

bool Camera::ObjectIsVisible(Rectangle const& bounds)
{
  return GetViewPort().intersects(bounds);
}

Camera::Vector2 Camera::WorldToScreen(Vector2 const& worldLocation)
{
  return worldLocation - _position;
}

Camera::Rectangle Camera::WorldToScreen(Rectangle const& worldRectangle)
{
  return Rectangle(worldRectangle.left - (int)_position.x,
                 worldRectangle.top - (int)_position.y,
                 worldRectangle.width, worldRectangle.height);
}

Camera::Vector2 Camera::ScreenToWorld(Vector2 const& screenLocation)
{
  return screenLocation + _position;
}

Camera::Rectangle Camera::ScreenToWorld(Rectangle const& screenRectangle)
{
  return Rectangle(screenRectangle.left + (int)_position.x,
                 screenRectangle.top + (int)_position.y,
                 screenRectangle.width, screenRectangle.height);
}

Camera::Vector2 Camera::_position;
Camera::Vector2 Camera::_viewPortSize;
Camera::Rectangle Camera::_worldRectangle;
}

