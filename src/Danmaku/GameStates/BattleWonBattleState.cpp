#include "Danmaku/BattleWonBattleState.h"
#include "Danmaku/Battle.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/Party.h"

namespace Danmaku
{
int const BattleWonBattleState::XPPerEnemy(50000); // 25
int const BattleWonBattleState::XPPerConvincedEnemy(50);
int const BattleWonBattleState::XPFromBoss(2000);
int const BattleWonBattleState::XPFromConvincedBoss(4000);

BattleWonBattleState::BattleWonBattleState(CharVec& enemies)
  : _enemies(enemies), _frontRow(Party::GetInstance().GetFrontRow())
{
}

void BattleWonBattleState::Update(Battle& battle)
{
  battle.SetIdle();
  GameStateManager::SetState(GameStates::Ingame);
  int xpAwarded(0);
  Party& party = Party::GetInstance();

  for(auto* enemy : _enemies)
  {
    xpAwarded += enemy->IsConvinced() ? XPPerConvincedEnemy : XPPerEnemy;
  }

  if(battle.IsBossFight())
    xpAwarded += _enemies[0]->IsConvinced() ? XPFromConvincedBoss : XPFromBoss;

  if(party.GetAveragePartyLvl() == 0)
    return;
  xpAwarded /= party.GetAveragePartyLvl() - _enemies[0]->GetLvl() == 0 ?
        1 :
        party.GetAveragePartyLvl() - _enemies[0]->GetLvl();

  for(auto* chara : _frontRow)
  {
    chara->GetStats().ReduceBuffEffectiveness(10);
    chara->EndBattle();
  }

  for(auto* enemy : _enemies)
    delete enemy;

  party.AddExperience(xpAwarded);
}

void BattleWonBattleState::Draw(Battle &battle, sf::RenderTarget &rTarget)
{
}

}
