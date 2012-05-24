#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Battle.h"

namespace Danmaku
{
Battle::Battle()
  : _battleState(Idle)
{
}

bool Battle::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Battle;
}

bool Battle::Update()
{
  return false;
}

bool Battle::DrawCondition()
{
  return GameStateManager::GetState() == GameStates::Battle;
}

void Battle::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
}
}
