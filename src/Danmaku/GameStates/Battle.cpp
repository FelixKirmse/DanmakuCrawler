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

  _fourLayout.push_back(sf::Vector2f(230.f, 305.f));
  _fourLayout.push_back(sf::Vector2f(380.f, 340.f));
  _fourLayout.push_back(sf::Vector2f(480.f, 275.f));
  _fourLayout.push_back(sf::Vector2f(650.f, 350.f));
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
    Draw(renderTarget);
    break;
  case BattleMenu:   
    Draw(renderTarget);
    _battleMenu.Draw(renderTarget);
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
  _currentInstance->_enemies.push_back(Character("Enemy0"));
  _currentInstance->_enemies.push_back(Character("Enemy1"));
  _currentInstance->_enemies.push_back(Character("Enemy6"));
  _currentInstance->_enemies.push_back(Character("Enemy7"));
  _currentInstance->_enemies[0].GetStats().SPD[0] = 118.f;
  _currentInstance->_enemies[0].InitializeCharFrame();
  _currentInstance->_enemies[0].Graphics().UpdateHP();
  _currentInstance->_enemies[0].Graphics().UpdateMP();

  _currentInstance->_enemies[1].GetStats().SPD[0] = 108.f;
  _currentInstance->_enemies[1].InitializeCharFrame();
  _currentInstance->_enemies[1].Graphics().UpdateHP();
  _currentInstance->_enemies[1].Graphics().UpdateMP();

  _currentInstance->_enemies[2].GetStats().SPD[0] = 120.f;
  _currentInstance->_enemies[2].InitializeCharFrame();
  _currentInstance->_enemies[2].Graphics().UpdateHP();
  _currentInstance->_enemies[2].Graphics().UpdateMP();

  _currentInstance->_enemies[3].GetStats().SPD[0] = 115.f;
  _currentInstance->_enemies[3].InitializeCharFrame();
  _currentInstance->_enemies[3].Graphics().UpdateHP();
  _currentInstance->_enemies[3].Graphics().UpdateMP();

  _currentInstance->_playerRow.push_back(Character("Youmu"));
  _currentInstance->_playerRow.push_back(Character("Mokou"));
  _currentInstance->_playerRow.push_back(Character("Mystia"));
  _currentInstance->_playerRow.push_back(Character("Alice"));
  _currentInstance->_playerRow[0].GetStats().SPD[0] = 100.f;
  _currentInstance->_playerRow[0].InitializeCharFrame();
  _currentInstance->_playerRow[0].Graphics().UpdateHP();
  _currentInstance->_playerRow[0].Graphics().UpdateMP();

  _currentInstance->_playerRow[1].GetStats().SPD[0] = 122.f;
  _currentInstance->_playerRow[1].InitializeCharFrame();
  _currentInstance->_playerRow[1].Graphics().UpdateHP();
  _currentInstance->_playerRow[1].Graphics().UpdateMP();

  _currentInstance->_playerRow[2].GetStats().SPD[0] = 130.f;
  _currentInstance->_playerRow[2].InitializeCharFrame();
  _currentInstance->_playerRow[2].Graphics().UpdateHP();
  _currentInstance->_playerRow[2].Graphics().UpdateMP();

  _currentInstance->_playerRow[3].GetStats().SPD[0] = 115.f;
  _currentInstance->_playerRow[3].InitializeCharFrame();
  _currentInstance->_playerRow[3].Graphics().UpdateHP();
  _currentInstance->_playerRow[3].Graphics().UpdateMP();

  _currentInstance->SetInitialSPD(_currentInstance->_enemies);
  _currentInstance->SetInitialSPD(_currentInstance->_playerRow);
  _currentInstance->ArrangeCharFrames(bossID);
}

void Battle::IdleUpdate()
{
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
}


void Battle::ConsequenceUpdate()
{
  ++_frameCounter;
  if(_frameCounter == 45)
  {
    _battleState = Idle;
    _frameCounter = 0;

    // TODO Remove if after testing
    if(_enemies[0].CurrentHP() <= 0.f)
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


void Battle::Draw(sf::RenderTarget& renderTarget)
{
  if(_enemies.size() == 4)
  {
    _enemies[2].Graphics().DrawBattleSprite(renderTarget);
    _enemies[0].Graphics().DrawBattleSprite(renderTarget);
    _enemies[1].Graphics().DrawBattleSprite(renderTarget);
    _enemies[3].Graphics().DrawBattleSprite(renderTarget);
  }
  else
  {
    _enemies[1].Graphics().DrawBattleSprite(renderTarget);
    _enemies[0].Graphics().DrawBattleSprite(renderTarget);
    _enemies[3].Graphics().DrawBattleSprite(renderTarget);
  }

  // CharSprite infront of enemies, but behind CharFrames
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i].Graphics().DrawCharSprite(renderTarget);
  }

  // CharFrames ontop
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i].Graphics().Draw(renderTarget);
  }  
}

void Battle::ConsequenceDraw(sf::RenderTarget& renderTarget)
{
  Draw(renderTarget);
}


void Battle::ArrangeCharFrames(int bossID)
{
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i].Graphics().Reposition(FrameContainerStart.x
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
    _enemies[i].Graphics().SetBattleSpritePosition(positions[i]);
  }
}

void Battle::SetInitialSPD(CharVec& vec)
{
  for(size_t i = 0; i < vec.size(); ++i)
  {
    vec[i].TurnCounter() = vec[i].GetStats().SPD[0];
  }
}

}
