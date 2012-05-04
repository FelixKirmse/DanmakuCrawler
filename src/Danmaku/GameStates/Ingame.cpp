#include "Danmaku/Ingame.h"

namespace Danmaku
{
Ingame::Ingame()
 // : _tileMap(TileMap<Map<TileCode>, TileCode>::GetInstance())
{
}

bool Ingame::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Ingame;
}

bool Ingame::Update()
{
  return false;
}

bool Ingame::DrawCondition()
{
  GameStates::States state(GameStateManager::GetState());
  return state == GameStates::Ingame ||
      (state == GameStates::Menu && Menu::GetState() == MenuStates::Ingame);
}

void Ingame::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
}
}
