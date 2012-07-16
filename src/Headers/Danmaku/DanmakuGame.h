#pragma once
#include <memory>
#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/TileCode.h"
#include "Danmaku/MapCell.h"
#include "Danmaku/Party.h"

namespace Danmaku
{
class DanmakuGame : public BlackDragonEngine::Game
{
public:
  typedef BlackDragonEngine::TileMap<BlackDragonEngine::Map<MapCell, TileCode>,
  MapCell, TileCode> DanmakuMap;
  typedef std::unique_ptr<DanmakuMap> MapPtr;

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
  void LoadTexturesFromDir(sf::String const& dir, sf::String const& suffix);

  GameStateManager _stateManager;
  MapPtr _tileMap;
  Party _party;
};
}
