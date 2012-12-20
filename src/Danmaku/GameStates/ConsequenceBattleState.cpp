#include "Danmaku/ConsequenceBattleState.h"
#include "Danmaku/Battle.h"
#include "Danmaku/Party.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Spells/ISpell.h"

namespace Danmaku
{
int const ConsequenceBattleState::ConsequenceFrames(90);

ConsequenceBattleState::ConsequenceBattleState(CharVec& enemies)
  : _frameCounter(0), _frontRow(Party::GetInstance().GetFrontRow()),
    _enemies(enemies), _charHPStep(),_charHPShouldHave()
{
}

void ConsequenceBattleState::Update(Battle& battle)
{
  Character* currentAttacker = battle.GetCurrentAttacker();
  TargetInfo& targetInfo = battle.GetTargetInfo();
  _enemyTurn = battle.IsEnemyTurn();

  ++_frameCounter;
  if(_frameCounter == ConsequenceFrames)
  {
    battle.SetIdle();
    _frameCounter = 0;
    currentAttacker->Graphics().UpdateSPD(false);

    for(size_t i = 0; i < _frontRow.size(); ++i)
    {
      _frontRow[i]->CurrentHP() = _charHPShouldHave[i];
      _frontRow[i]->Graphics().UpdateHP();
      _frontRow[i]->CheckIfDead();
      _frontRow[i]->ResetDamageDisplay();
    }

    bool someoneAlive(false); // Pretend every player is dead...
    for(auto* player : _frontRow)
    {
      someoneAlive |= !player->IsDead(); // ...until we find someone alive!
    }

    if(!someoneAlive) // whoops, everyone is dead, Game Over!
    {
      // TODO Actual Game Over Code
      battle.GameOver();
      GameStateManager::SetState(GameStates::Titlescreen);
    }

    bool enemyAlive(false); // Pretend every enemy is dead...
    for(auto* enemy : _enemies)
    {
      enemy->ResetDamageDisplay();
      enemy->CheckIfDead();
      enemyAlive |= !enemy->IsDead(); // ...until proven otherwise.
    }

    if(!enemyAlive) // FUCK YEAH, WE KILLED THEM FUCKERS!
      battle.BattleWon();

    return;
  }

  if(_frameCounter > 1)
  {
    for(size_t i = 0; i < _frontRow.size(); ++i)
    {
      _frontRow[i]->CurrentHP() -= _charHPStep[i];
      _frontRow[i]->Graphics().UpdateHP();
    }
    return;
  }
  currentAttacker->UseMP(targetInfo.Spell->GetMPCost(*currentAttacker));
  bool targetIsEnemy(battle.TargetIsEnemy());

  float charHPBefore[4];
  for(size_t i = 0; i < _frontRow.size(); ++i)
  {
    charHPBefore[i] = _frontRow[i]->CurrentHP();
  }

  TargetInfo::TargetType targetType(targetInfo.Spell->GetTargetType());
  if(targetType == TargetInfo::Single)
    targetInfo.Spell->DamageCalculation(*currentAttacker, *targetInfo.Target);
  else if(targetType == TargetInfo::Self)
    targetInfo.Spell->DamageCalculation(*currentAttacker, *currentAttacker);
  else if(targetType == TargetInfo::Allies || targetType == TargetInfo::Enemies)
  {
    bool attackerIsEnemy(battle.AttackerIsEnemy());
    bool targetIsPlayer((attackerIsEnemy && targetType != TargetInfo::Allies) ||
                        (!attackerIsEnemy && targetType == TargetInfo::Allies));
    for(size_t i = 0; i < (targetIsPlayer ? _frontRow.size() :
                           _enemies.size()); ++i)
      targetInfo.Spell->DamageCalculation(*currentAttacker,
                                           targetIsPlayer ? *_frontRow[i] :
                                                            *_enemies[i]);
  }
  else if(targetInfo.Spell->GetTargetType() == TargetInfo::Decaying)
  {
    targetInfo.Spell->DamageCalculation(*currentAttacker, *targetInfo.Target);

    size_t attackerIndex = 0;
    for(;attackerIndex < (targetIsEnemy ? _enemies.size() :
                          _frontRow.size()) &&
        (_enemyTurn ?
         _frontRow[attackerIndex] :
         _enemies[attackerIndex]) != targetInfo.Target;
        ++attackerIndex); //This loop has no body intentionally!!!!
    for(int i = attackerIndex - 1, mod = 2; i >= 0; --i, ++mod)
      targetInfo.Spell->DamageCalculation(*currentAttacker,
                                           targetIsEnemy ? *_enemies[i] :
                                                           *_frontRow[i], mod);

    for(size_t i = attackerIndex + 1, mod = 2;
        i < (targetIsEnemy ? _enemies.size() : _frontRow.size());
        ++i, ++mod)
      targetInfo.Spell->DamageCalculation(*currentAttacker,
                                           targetIsEnemy ? *_enemies[i] :
                                                           *_frontRow[i], mod);
  }
  _enemyTurn = false;
  if(targetIsEnemy)
    for(auto* enemy : _enemies)
      enemy->Graphics().UpdateHP();

  for(size_t i = 0; i < _frontRow.size(); ++i)
  {
    _charHPShouldHave[i] = _frontRow[i]->CurrentHP();
    _charHPStep[i] = (charHPBefore[i] - _frontRow[i]->CurrentHP())
        / ConsequenceFrames;
    _frontRow[i]->CurrentHP() = charHPBefore[i] - _charHPStep[i];
    _frontRow[i]->Graphics().UpdateHP();
    _frontRow[i]->Graphics().UpdateMP();
  }
}

void ConsequenceBattleState::Draw(Battle& battle, sf::RenderTarget& rTarget)
{
  for(auto* enemy : _enemies)
    enemy->Graphics().DrawDamageDone(rTarget);

  for(auto* player : _frontRow)
    player->Graphics().DrawDamageDone(rTarget);
}
}
