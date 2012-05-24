#include "Danmaku/TitleScreen.h"
#include "Danmaku/Menu.h"
#include "Danmaku/Ingame.h"
#include "Danmaku/GameStateManager.h"

namespace Danmaku
{
State GameStateManager::_state = GameStates::Titlescreen;
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
  using namespace std;
  shared_ptr<TitleScreen> titleScreen(new TitleScreen());
  AddUpdateableState(titleScreen);
  AddDrawableState(titleScreen);

  shared_ptr<Menu> menu(new Menu());
  AddUpdateableState(menu);
  AddDrawableState(menu);

  shared_ptr<Ingame> ingame(new Ingame());
  AddUpdateableState(ingame);
  AddDrawableState(ingame);
}
}
