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
class TitleScreen : public BlackDragonEngine::IDrawableGameState,
    public BlackDragonEngine::IUpdateableGameState
{
public:
  typedef BlackDragonEngine::Provider<sf::Texture> TextureProvider;

  TitleScreen();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renterTarget);
  bool UpdateCondition();
  bool Update();

private:
  sf::Sprite _titleSprite;
};
}
