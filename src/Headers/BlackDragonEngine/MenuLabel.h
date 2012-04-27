#pragma once
#include "BlackDragonEngine/Provider.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
using namespace sf;

class MenuLabel
{
public:
  MenuLabel(String const& text, String const& fontName);
  void Draw(RenderTarget& renderTarget);

  String const& GetText();
  Vector2f const& GetPosition();

  void SetText(String const& text);
  void SetPosition(Vector2f const& position);

private:
  Text _text;
};
}
