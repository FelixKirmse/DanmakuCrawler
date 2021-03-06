#pragma once
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "Danmaku/TileCode.h"
#include "Danmaku/OverworldPlayer.h"
#include "Danmaku/MapCell.h"

namespace Danmaku
{
class Ingame : public BlackDragonEngine::IUpdateableGameState,
    public BlackDragonEngine::IDrawableGameState
{
public:  
  typedef BlackDragonEngine::TileMap<BlackDragonEngine::Map<MapCell, TileCode>,
  MapCell, TileCode> DanmakuMap;

  Ingame();
  bool UpdateCondition();
  bool Update();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);

  static void NewGame();
private:
  void Reset();

  DanmakuMap& _tileMap;
  OverworldPlayer _player;

  static Ingame* _instance;
};
}
