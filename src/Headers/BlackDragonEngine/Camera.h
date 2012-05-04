#pragma once
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
template<class TMap, class TCodes>
class TileMap;

class Camera
{
public:
  typedef sf::Vector2f Vector2;
  typedef sf::IntRect Rectangle;

  static void ForcePosition(Vector2 const& position);
  static void SetPosition(Vector2 const& position);
  static Vector2 const& GetPosition();
  static void SetWorldRectangle(Rectangle const& worldRectangle);
  static Rectangle const& GetWorldRectangle();
  static void SetViewPortWidth(float width);
  static int GetViewPortWidth();
  static void SetViewPortheight(float height);
  static int GetViewPortHeight();
  static Rectangle GetViewPort();

  static void Move(Vector2 const& offset);
  static bool ObjectIsVisible(Rectangle const& bounds);
  static Vector2 WorldToScreen(Vector2 const& worldLocation);
  static Rectangle WorldToScreen(Rectangle const& worldRectangle);

  static Vector2 ScreenToWorld(Vector2 const& screenLocation);
  static Rectangle ScreenToWorld(Rectangle const& screenRectangle);

  template<class TMap, class TCodes>
  static void UpdateWorldRectangle(TileMap<TMap, TCodes> const& tileMap);

private:
  static Vector2 _position;
  static Vector2 _viewPortSize;
  static Rectangle _worldRectangle;
};

#include "BlackDragonEngine/Inline/Camera.inl"
}
