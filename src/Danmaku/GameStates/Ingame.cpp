#include "BlackDragonEngine/Camera.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Menu.h"
#include "Danmaku/TileList.h"
#include "Danmaku/Ingame.h"

namespace Danmaku
{
Ingame::Ingame()
  : _tileMap(DanmakuMap::GetInstance()),
    _player(BlackDragonEngine::Provider<sf::Texture>::Get("OverworldPlayer"))
{  
  BlackDragonEngine::Input::AddNewAction("MapSave", {sf::Keyboard::F2});
  _instance = this;
}

bool Ingame::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Ingame;
}

bool Ingame::Update()
{
  using namespace BlackDragonEngine;
  if(Input::Cancel())
  {
    GameStateManager::SetState(GameStates::Menu);
    Danmaku::Menu::SetState(MenuStates::Ingame);
  }
  if(Input::TriggeredAction("MapSave", true))
  {
    DanmakuMap::GetInstance().SaveToFile("map.png");
  }
  _player.Update();
  return false;
}

bool Ingame::DrawCondition()
{
  GameStates::States state(GameStateManager::GetState());
  return state == GameStates::Ingame;
}

void Ingame::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
  _tileMap.Draw(renderTarget);
  _player.Draw(renderTarget);
}

Ingame* Ingame::_instance;

void Ingame::NewGame()
{
  _instance->Reset();
}

void Ingame::Reset()
{
  using namespace BlackDragonEngine;
  using namespace sf;
  _player = OverworldPlayer(Provider<Texture>::Get("OverworldPlayer"));
}
}
