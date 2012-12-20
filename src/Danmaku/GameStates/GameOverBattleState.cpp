#include "Danmaku/GameOverBattleState.h"
#include "Danmaku/Battle.h"

namespace Danmaku
{
void GameOverBattleState::Update(Battle& battle)
{
  battle.BattleWon();
}

void GameOverBattleState::Draw(Battle& battle, sf::RenderTarget& rTarget)
{
}
}
