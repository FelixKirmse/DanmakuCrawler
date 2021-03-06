#pragma once
#include "BlackDragonEngine/StateManager.h"
#include "Danmaku/States.h"

namespace Danmaku
{
typedef GameStates::States State;

class GameStateManager : public BlackDragonEngine::StateManager
{
private:
  static State _state;
  static bool _playerDead;
  static bool _fastDead;

public:
  GameStateManager();
  void Initialize();
  static State GetState();
  static void SetState(State state);
  static bool GetPlayerDead();
  static void SetPlayerDead(bool dead);
  static bool GetFastDead();
};
}
