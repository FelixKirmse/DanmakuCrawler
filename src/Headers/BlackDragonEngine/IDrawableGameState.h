#pragma once
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
class IDrawableGameState
{
public:
  virtual ~IDrawableGameState() {}
  virtual bool DrawCondition() = 0;
  virtual void Draw(float interpolation, sf::RenderTarget& renderTarget) = 0;
};
}
