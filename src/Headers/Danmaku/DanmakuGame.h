#pragma once
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/GameStateManager.h"

namespace Danmaku
{
using namespace std;
using namespace BlackDragonEngine;

class DanmakuGame : public Game
{
private:
  GameStateManager _stateManager;

protected:
  void LoadContent();
  void Initialize();
  void Update();
  void Draw(float interpolation, RenderTarget& renderTarget);

public:
  static int const ResolutionWidth = 640;
  static int const ResolutionHeight = 480;

  DanmakuGame();
  void OnLevelLoad();
};
}
