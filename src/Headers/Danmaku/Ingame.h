#pragma once
#include <map>
#include <boost/unordered_map.hpp>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "BlackDragonEngine/Camera.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Menu.h"
#include "Danmaku/TileCode.h"
#include "Danmaku/OverworldPlayer.h"
#include "Danmaku/TileList.h"
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

private:
  DanmakuMap& _tileMap;
  OverworldPlayer _player;
};
}
