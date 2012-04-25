#include "Danmaku/GameStateManager.h"

namespace Danmaku
{
State GameStateManager::_state = States::Titlescreen;
bool GameStateManager::_playerDead;
bool GameStateManager::_fastDead;

GameStateManager::GameStateManager()
  : StateManager()
{
}

State GameStateManager::GetState()
{
  return _state;
}

void GameStateManager::SetState(State state)
{
  _state = state;
}

bool GameStateManager::GetPlayerDead()
{
  return _playerDead;
}

void GameStateManager::SetPlayerDead(bool dead)
{
  _playerDead = dead;
}

bool GameStateManager::GetFastDead()
{
  return _fastDead;
}

void GameStateManager::Initialize()
{
  shared_ptr<TitleScreen> titleScreen(new TitleScreen());
  AddUpdateableState(titleScreen);
  AddDrawableState(titleScreen);
}
}
