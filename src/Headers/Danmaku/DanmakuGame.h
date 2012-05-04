#pragma once
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/Provider.h"
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/TileCode.h"

namespace Danmaku
{
class DanmakuGame : public BlackDragonEngine::Game
{
public:
  typedef BlackDragonEngine::Provider<sf::Texture> TextureProvider;
  typedef BlackDragonEngine::Provider<sf::Font> FontProvider;
  typedef BlackDragonEngine::TileMap<BlackDragonEngine::Map<TileCode>, TileCode>
  DanmakuMap;

  DanmakuGame();
  void OnLevelLoad();

  static int const ResolutionWidth = 640;
  static int const ResolutionHeight = 480;

protected:
  void LoadContent();
  void Initialize();
  void Update();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);

private:
  GameStateManager _stateManager;
};
}
