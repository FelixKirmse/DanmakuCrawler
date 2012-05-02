#pragma once
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
using namespace sf;

template<class TMap, class TCodes>
class TileMap;

class Camera
{
public:
  static void ForcePosition(Vector2f const& position);
  static void SetPosition(Vector2f const& position);
  static Vector2f const& GetPosition();
  static void SetWorldRectangle(IntRect const& worldRectangle);
  static IntRect const& GetWorldRectangle();
  static void SetViewPortWidth(float width);
  static int GetViewPortWidth();
  static void SetViewPortheight(float height);
  static int GetViewPortHeight();
  static IntRect GetViewPort();

  static void Move(Vector2f const& offset);
  static bool ObjectIsVisible(IntRect const& bounds);
  static Vector2f WorldToScreen(Vector2f const& worldLocation);
  static IntRect WorldToScreen(IntRect const& worldRectangle);

  static Vector2f ScreenToWorld(Vector2f const& screenLocation);
  static IntRect ScreenToWorld(IntRect const& screenRectangle);

  template<class TMap, class TCodes>
  static void UpdateWorldRectangle(TileMap<TMap, TCodes> const& tileMap);

private:
  static Vector2f _position;
  static Vector2f _viewPortSize;
  static IntRect _worldRectangle;
};

#include "BlackDragonEngine/Inline/Camera.inl"
}
