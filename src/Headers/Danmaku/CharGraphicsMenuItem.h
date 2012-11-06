#pragma once
#include "BlackDragonEngine/MenuItem.h"
#include <SFML/Graphics.hpp>


namespace Danmaku
{
class CharGraphics;

class CharGraphicsMenuItem : public BlackDragonEngine::MenuItem
{
public:
  CharGraphicsMenuItem(CharGraphics& graphics, sf::String const& name);

  void Update();
  void Draw(sf::RenderTarget& renderTarget);

  void SetPosition(sf::Vector2f const& position);

private:
  CharGraphics& _charGraphics;
  sf::RectangleShape _edge;
};
}
