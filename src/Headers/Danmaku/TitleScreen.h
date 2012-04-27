#pragma once
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"


namespace Danmaku
{
using namespace BlackDragonEngine;
using namespace sf;

class TitleScreen : public IDrawableGameState, public IUpdateableGameState
{
public:
  TitleScreen();
  bool DrawCondition();
  void Draw(float interpolation, RenderTarget& renterTarget);
  bool UpdateCondition();
  bool Update();

private:
  Sprite _titleSprite;
};
}
