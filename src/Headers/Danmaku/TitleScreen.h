#pragma once
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"

namespace Danmaku
{
class TitleScreen : public BlackDragonEngine::IDrawableGameState,
    public BlackDragonEngine::IUpdateableGameState
{
public:
  TitleScreen();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renterTarget);
  bool UpdateCondition();
  bool Update();

private:
  sf::Sprite _titleSprite;
};
}
