#include <string>
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Battle.h"
#include "Danmaku/Party.h"
#include "Danmaku/Spells/ISpell.h"
#include "boost/format.hpp"

namespace Danmaku
{
Battle* Battle::_currentInstance;

Battle::Battle()
  : _battleState(Idle), _enemies(), _playerRow(Party::GetFrontRow()),
    _playerBattleParty(Party::GetBackSeat()), _currentAttacker(0),
    _enemyLeftOff(0), _playerLeftOff(0), _frameCounter(0), _enemyTurn(false),
    _battleMenu(*this)
{
  _currentInstance = this;
}

bool Battle::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Battle;
}

bool Battle::Update()
{
  switch(_battleState)
  {
  case Idle:
    IdleUpdate();
    break;
  case BattleMenu:
    _battleMenu.Update();
    break;
  case Action:
    break;
  case Consequences:
    ConsequenceUpdate();
    break;
  case GameOver:
    break;
  case BattleWon:
    break;
  }
  return false;
}

bool Battle::DrawCondition()
{
  return GameStateManager::GetState() == GameStates::Battle;
}

void Battle::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
  switch(_battleState)
  {
  case Idle:
    IdleDraw(renderTarget);
    break;
  case BattleMenu:   
    IdleDraw(renderTarget);
    break;
  case Action:
    break;
  case Consequences:
    ConsequenceDraw(renderTarget);
    break;
  case GameOver:
    break;
  case BattleWon:
    break;
  }
}

void Battle::StartBattle(int level, int bossID)
{
  GameStateManager::SetState(GameStates::Battle);
  // TODO enemy generation code
  _currentInstance->_enemies.clear();
  _currentInstance->_playerRow.clear();
  _currentInstance->_enemies.push_back(Character("Nitori"));
  _currentInstance->_playerRow.push_back(Character("Cirno"));
  _currentInstance->_playerRow[0].GetStats().SPD[0] = 125.f;
  _currentInstance->_playerRow[0].InitializeCharFrame();
  _currentInstance->_playerRow[0]._charFrame.Reposition(sf::Vector2f(200.f, 370.f));
  _currentInstance->_playerRow[0]._charFrame.UpdateHP();
  _currentInstance->_playerRow[0]._charFrame.UpdateMP();
}

void Battle::IdleUpdate()
{
  for(size_t i = _enemyLeftOff; i < _enemies.size(); ++i)
  {
    if(_enemies[i].UpdateTurnCounter())
    {
      _targetInfo = _enemies[i].AIBattleMenu(_playerRow);

      //TODO Delete this line after testing
      _battleState = Consequences;

      //_battleState = Action;
      _enemyLeftOff = i;
      _currentAttacker = &_enemies[i];
      return;
    }
  }

  _enemyLeftOff = 0;

  for(size_t i = _playerLeftOff; i < _playerRow.size(); ++i)
  {    
    if(_playerRow[i].UpdateTurnCounter())
    {
      _battleState = BattleMenu;
      _playerLeftOff = i;
      _currentAttacker = &_playerRow[i];
      return;
    }
  }

  _playerLeftOff = 0;
}


void Battle::ConsequenceUpdate()
{
  ++_frameCounter;
  if(_frameCounter == 45)
  {
    _battleState = Idle;
    _frameCounter = 0;

    // TODO Remove if after testing
    if(_enemies[0]._currentHP <= 0.f)
    {
      _battleState = Idle;
      GameStateManager::SetState(GameStates::Ingame);
    }
    return;
  }
  if(_frameCounter > 1)
    return;

  if(_targetInfo.TargetType == TargetInfo::Single)
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_targetInfo.Target);

  CharVec& affectedParty = (_enemyTurn ? _playerRow : _enemies);

  if(_targetInfo.TargetType == TargetInfo::All)
  {
    for(size_t i = 0; i < affectedParty.size(); ++i)
    {
      _targetInfo.Spell->DamageCalculation(*_currentAttacker, affectedParty[i]);
    }
  }

  if(_targetInfo.TargetType == TargetInfo::Decaying)
  {
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_targetInfo.Target);
    size_t attackerIndex = 0;
    for(;attackerIndex < affectedParty.size() &&
        &affectedParty[attackerIndex] != _targetInfo.Target;
        ++attackerIndex); //This loop has no body intentionally!!!!
    for(int i = attackerIndex - 1, mod = 1; attackerIndex >= 0; --i, ++mod)
    {
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           affectedParty[i], mod);
    }

    for(int i = attackerIndex + 1, mod = 1;
        attackerIndex < affectedParty.size();
        ++i, ++mod)
    {
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           affectedParty[i], mod);
    }
  }
}


void Battle::IdleDraw(sf::RenderTarget& renderTarget)
{
  _playerRow[0]._charFrame.Draw(renderTarget);
  float val1(_playerRow[0]._charFrame._spdBar.getSize().x);
  float val2((float)_playerRow[0]._turnCounter / _playerRow[0].TimeToAction);
  sf::Text debug(std::to_string(val1) + " \n " + std::to_string(val2));
  debug.setPosition(20,10);
  renderTarget.draw(debug);
  _battleMenu.Draw(renderTarget);
}

void Battle::ConsequenceDraw(sf::RenderTarget& renderTarget)
{
  IdleDraw(renderTarget);
}
}
