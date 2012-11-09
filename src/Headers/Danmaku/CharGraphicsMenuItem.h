#pragma once
#include "BlackDragonEngine/MenuItem.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Danmaku/CharGraphics.h"


namespace Danmaku
{
class CharGraphics;

class CharGraphicsMenuItem : public BlackDragonEngine::MenuItem
{
public:
  CharGraphicsMenuItem(CharGraphics graphics, int id);

  void Update();
  void Draw(sf::RenderTarget& renderTarget);

  void SetPosition(sf::Vector2f const& position);
  sf::Vector2f const& GetPosition();
  sf::FloatRect GetLocalRectangle();

  int GetIndex();

private:
  CharGraphics _charGraphics;
  sf::RectangleShape _edge;
  int _index;
};
}
