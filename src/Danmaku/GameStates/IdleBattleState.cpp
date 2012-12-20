#include "Danmaku/IdleBattleState.h"
#include "Danmaku/Party.h"
#include "Danmaku/Battle.h"
#include "Danmaku/StatOverview.h"

namespace Danmaku
{
IdleBattleState::IdleBattleState(CharVec& enemies)
  : _playerLeftOff(0), _enemyLeftOff(0),
    _frontRow(Party::GetInstance().GetFrontRow()),
    _enemies(enemies)
{
}

void IdleBattleState::Update(Battle& battle)
{
  for(size_t i = _playerLeftOff; i < _frontRow.size(); ++i)
  {
    if(_frontRow[i]->UpdateTurnCounter())
    {
      battle.ShowBattleMenu();
      _playerLeftOff = i + 1;
      battle.SetCurrentAttacker(_frontRow[i]);
      battle.IsEnemyTurn(false);
      StatOverview::GetInstance().Update(*_frontRow[i]);
      return;
    }
  }

  _playerLeftOff = 0;


  for(size_t i = _enemyLeftOff; i < _enemies.size(); ++i)
  {
    if(_enemies[i]->UpdateTurnCounter())
    {
      battle.SetTargetInfo(_enemies[i]->AIBattleMenu(_frontRow));
      battle.PerformAction();
      _enemyLeftOff = i + 1;
      battle.SetCurrentAttacker(_enemies[i]);
      battle.IsEnemyTurn(true);
      return;
    }
  }

  _enemyLeftOff = 0;
}

void IdleBattleState::Draw(Battle& battle, sf::RenderTarget& rTarget)
{
}
}
