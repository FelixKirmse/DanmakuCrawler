#include "BlackDragonEngine/Camera.h"

namespace BlackDragonEngine
{
static inline float clamp(float x, float a, float b)
{
  return x < a ? a : (x > b ? b : x);
}

void Camera::ForcePosition(Vector2f const& position)
{
  _position = position;
}

void Camera::SetPosition(Vector2f const& position)
{
  _position = Vector2f(
        clamp(position.x, _worldRectangle.left,
              _worldRectangle.width - GetViewPortWidth()),
        clamp(position.y, _worldRectangle.top,
              _worldRectangle.height - GetViewPortHeight()));
}

Vector2f const& Camera::GetPosition()
{
  return _position;
}

void Camera::SetWorldRectangle(IntRect const& worldRectangle)
{
  _worldRectangle = worldRectangle;
}

IntRect const& Camera::GetWorldRectangle()
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

void Camera::SetViewPortheight(float height)
{
  _viewPortSize.y = height;
}

int Camera::GetViewPortHeight()
{
  return (int)_viewPortSize.y;
}

IntRect Camera::GetViewPort()
{
  return IntRect((int)_position.x, (int)_position.y, GetViewPortWidth(),
                 GetViewPortHeight());
}

void Camera::Move(Vector2f const& offset)
{
  _position += offset;
}

bool Camera::ObjectIsVisible(IntRect const& bounds)
{
  return GetViewPort().intersects(bounds);
}

Vector2f Camera::WorldToScreen(Vector2f const& worldLocation)
{
  return worldLocation - _position;
}

IntRect Camera::WorldToScreen(IntRect const& worldRectangle)
{
  return IntRect(worldRectangle.left - (int)_position.x,
                 worldRectangle.top - (int)_position.y,
                 worldRectangle.width, worldRectangle.height);
}

Vector2f Camera::ScreenToWorld(Vector2f const& screenLocation)
{
  return screenLocation + _position;
}

IntRect Camera::ScreenToWorld(IntRect const& screenRectangle)
{
  return IntRect(screenRectangle.left + (int)_position.x,
                 screenRectangle.top + (int)_position.y,
                 screenRectangle.width, screenRectangle.height);
}

Vector2f Camera::_position;
Vector2f Camera::_viewPortSize;
IntRect Camera::_worldRectangle;
}

