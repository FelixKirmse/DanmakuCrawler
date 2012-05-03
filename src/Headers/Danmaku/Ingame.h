#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "BlackDragonEngine/SimpleMapSquare.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Menu.h"
#include "Danmaku/TileCode.h"

namespace Danmaku
{
using namespace BlackDragonEngine;
using namespace std;
using namespace sf;

class Ingame : public IUpdateableGameState, public IDrawableGameState
{
public:
  Ingame();
  bool UpdateCondition();
  bool Update();
  bool DrawCondition();
  void Draw(float interpolation, RenderTarget& renderTarget);

private:
  //TileMap<Map<TileCode>, TileCode>& _tileMap;
};
}
