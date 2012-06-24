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
    _enemyLeftOff(0), _playerLeftOff(0), _frameCounter(0), _enemyTurn(false)
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
  _currentInstance->_enemies.push_back(Character("Enemy"));
  _currentInstance->_playerRow.push_back(Character("Player"));
  _currentInstance->_playerRow[0].GetStats().SPD[0] = 125.f;
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
      //TODO delete following 2 lines after testing
      _targetInfo = _playerRow[i].AIBattleMenu(_enemies);
      _battleState = Consequences;

      //_battleState = BattleMenu;
      _playerLeftOff = 0;
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
  using namespace sf;
  using namespace boost;

  Character& enemy = _enemies[0];
  Character& player = _playerRow[0];

  /*Text enemyText(str(format("%1%\nHP: %2%/%3%\nSPD: %4%/%5%")
                     % enemy._name % (int)enemy._currentHP
                     % (int)enemy._stats.GetTotalHP()
                     % enemy._turnCounter % enemy.TimeToAction));
  Text playerText(str(format("%1%\nHP: %2%/%3%\nSPD: %4%/%5%")
                      % player._name % (int)player._currentHP
                      % (int)player._stats.GetTotalHP()
                      % player._turnCounter % player.TimeToAction));*/

  Text enemyText(enemy._name + "\nHP: "
                 + std::to_string((int)enemy._currentHP) + "/"
                 + std::to_string((int)enemy._stats.GetTotalHP()) + "\nSPD: "
                 + std::to_string(enemy._turnCounter) + "/"
                 + std::to_string(enemy.TimeToAction));
  Text playerText(player._name + "\nHP: "
                 + std::to_string((int)player._currentHP) + "/"
                 + std::to_string((int)player._stats.GetTotalHP()) + "\nSPD: "
                 + std::to_string(player._turnCounter) + "/"
                 + std::to_string(player.TimeToAction));
  enemyText.setPosition(Vector2f(50, 200));
  playerText.setPosition(Vector2f(300, 200));
  renderTarget.draw(enemyText);
  renderTarget.draw(playerText);
  Text state((_battleState == Idle ? "Idle\n" : "Consequences\n")
             + std::to_string(_frameCounter));
  state.setPosition(Vector2f(50, 100));
  renderTarget.draw(state);
}

void Battle::ConsequenceDraw(sf::RenderTarget& renderTarget)
{
  IdleDraw(renderTarget);
}
}
