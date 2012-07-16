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
    _battleMenu(*this), _threeLayout(), _fourLayout()
{
  _currentInstance = this;
  _threeLayout.push_back(sf::Vector2f(260.f, 305.f));
  _threeLayout.push_back(sf::Vector2f(450.f, 255.f));
  _threeLayout.push_back(sf::Vector2f(625.f, 310.f));

  _fourLayout.push_back(sf::Vector2f(260.f, 305.f));
  _fourLayout.push_back(sf::Vector2f(380.f, 340.f));
  _fourLayout.push_back(sf::Vector2f(530.f, 275.f));
  _fourLayout.push_back(sf::Vector2f(625.f, 310.f));
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
  _currentInstance->_enemies.push_back(Character("Enemy1"));
  _currentInstance->_enemies.push_back(Character("Enemy2"));
  _currentInstance->_enemies.push_back(Character("Enemy3"));
  _currentInstance->_enemies.push_back(Character("Enemy8"));
  _currentInstance->_enemies[0].InitializeCharFrame();
  _currentInstance->_enemies[1].InitializeCharFrame();
  _currentInstance->_enemies[2].InitializeCharFrame();
  _currentInstance->_enemies[3].InitializeCharFrame();

  _currentInstance->_playerRow.push_back(Character("Youmu"));
  _currentInstance->_playerRow.push_back(Character("Enemy5"));
  _currentInstance->_playerRow.push_back(Character("Minoriko"));
  _currentInstance->_playerRow.push_back(Character("Marisa"));
  _currentInstance->_playerRow[0].GetStats().SPD[0] = 125.f;
  _currentInstance->_playerRow[0].InitializeCharFrame();
  _currentInstance->_playerRow[0]._charFrame.UpdateHP();
  _currentInstance->_playerRow[0]._charFrame.UpdateMP();

  _currentInstance->_playerRow[1].GetStats().SPD[0] = 105.f;
  _currentInstance->_playerRow[1].InitializeCharFrame();
  _currentInstance->_playerRow[1]._charFrame.UpdateHP();
  _currentInstance->_playerRow[1]._charFrame.UpdateMP();

  _currentInstance->_playerRow[2].GetStats().SPD[0] = 130.f;
  _currentInstance->_playerRow[2].InitializeCharFrame();
  _currentInstance->_playerRow[2]._charFrame.UpdateHP();
  _currentInstance->_playerRow[2]._charFrame.UpdateMP();

  _currentInstance->_playerRow[3].GetStats().SPD[0] = 115.f;
  _currentInstance->_playerRow[3].InitializeCharFrame();
  _currentInstance->_playerRow[3]._charFrame.UpdateHP();
  _currentInstance->_playerRow[3]._charFrame.UpdateMP();

  _currentInstance->ArrangeCharFrames();
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
  // Draw backwards for nice layering
  for(size_t i = _enemies.size() - 1; i != static_cast<size_t>(-1); --i)
  {
    _enemies[i]._charFrame.DrawBattleSprite(renderTarget);
  }

  // CharSprite infront of enemies, but behind CharFrames
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i]._charFrame.DrawCharSprite(renderTarget);
  }

  // CharFrames ontop
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i]._charFrame.Draw(renderTarget);
  }

  _battleMenu.Draw(renderTarget);
}

void Battle::ConsequenceDraw(sf::RenderTarget& renderTarget)
{
  IdleDraw(renderTarget);
}


void Battle::ArrangeCharFrames(int bossID)
{
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i]._charFrame.Reposition(FrameContainerStart.x
                                        + i * FrameContainerOffset,
                                        FrameContainerStart.y);
  }

  if(bossID != 0)
  {
    // TODO Boss Arrangement
    return;
  }

  VecVec& positions = (_enemies.size() == 3) ? _threeLayout : _fourLayout;
  for(size_t i = 0; i < _enemies.size(); ++i)
  {
    _enemies[i]._charFrame.SetBattleSpritePosition(positions[i]);
  }
}
}
