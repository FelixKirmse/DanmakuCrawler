#include <string>
#include <ctime>
#include <limits>
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Battle.h"
#include "Danmaku/Spells/ISpell.h"
#include "boost/format.hpp"
#include "Danmaku/Stats.h"

namespace Danmaku
{
Battle* Battle::_currentInstance;
size_t Battle::MaxEnemyID;
float const Battle::EnemyHPMod(5.f);
float const Battle::EnemyBaseMod(.4f);
int const Battle::ConsequenceFrames(90);

int const Battle::XPPerEnemy(250000);
int const Battle::XPPerConvincedEnemy(50);
int const Battle::XPFromBoss(2000);
int const Battle::XPFromConvincedBoss(4000);

Battle::Battle()
  : _battleState(Idle), _enemies(), _playerRow(Party::GetFrontRow()),
    _playerBattleParty(Party::GetBackSeat()), _currentAttacker(0),
    _enemyLeftOff(0), _playerLeftOff(0), _frameCounter(0), _enemyTurn(false),
    _battleMenu(*this), _threeLayout(), _fourLayout(), _charHPStep(),
    _charHPShouldHave(), _rng(time(0)), _queuedState(Idle), _changeState(false)
{
  _currentInstance = this;
  _threeLayout.push_back(sf::Vector2f(260.f, 305.f));
  _threeLayout.push_back(sf::Vector2f(450.f, 255.f));
  _threeLayout.push_back(sf::Vector2f(625.f, 310.f));

  _fourLayout.push_back(sf::Vector2f(230.f, 305.f));
  _fourLayout.push_back(sf::Vector2f(380.f, 340.f));
  _fourLayout.push_back(sf::Vector2f(480.f, 275.f));
  _fourLayout.push_back(sf::Vector2f(650.f, 340.f));
}

bool Battle::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Battle;
}

bool Battle::Update()
{
  if(_changeState)
  {
    _battleState = _queuedState;
    _changeState = false;
  }
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
  for(auto& chara : _playerRow)
    chara.Graphics().UpdateHP();
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

void Battle::SetTargetInfo(TargetInfo targetInfo)
{
  _targetInfo = targetInfo;
}

void Battle::SetBattleState(Battle::BattleState battleState)
{
  if(battleState == Action)
    battleState = Consequences;
  _queuedState = battleState;
  _changeState = true;
}

Battle::CharVec& Battle::GetEnemies()
{
  return _enemies;
}

Party::FrontRow& Battle::GetFrontRow()
{
  return _playerRow;
}

void Battle::StartBattle(int level, int bossID)
{
  _currentInstance->_isBossfight = bossID != 0;
  GameStateManager::SetState(GameStates::Battle);
  // TODO enemy generation code
  _currentInstance->_enemies.clear();

  _currentInstance->GenerateEnemies(level, bossID);

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
      SetBattleState(BattleMenu);
      _playerLeftOff = i + 1;
      _currentAttacker = &_playerRow[i];
      _battleMenu.SetCurrentAttacker(_currentAttacker);
      _enemyTurn = false;
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
      SetBattleState(Consequences);

      //_battleState = Action;
      _enemyLeftOff = i + 1;
      _currentAttacker = &_enemies[i];
      _enemyTurn = true;
      return;
    }
  }

  _enemyLeftOff = 0;
}


void Battle::ConsequenceUpdate()
{
  ++_frameCounter;
  if(_frameCounter == ConsequenceFrames)
  {
    _battleMenu.ResetMenu();
    SetBattleState(Idle);
    _frameCounter = 0;
    _currentAttacker->Graphics().UpdateSPD(false);

    for(size_t i = 0; i < _playerRow.size(); ++i)
    {
      _playerRow[i].CurrentHP() = _charHPShouldHave[i];
      _playerRow[i].Graphics().UpdateHP();
      _playerRow[i].CheckIfDead();
      _playerRow[i].ResetDamageDisplay();
    }

    bool someoneAlive(false); // Pretend every player is dead...
    for(auto& player : _playerRow)
    {
      someoneAlive |= !player.IsDead(); // ...until we find someone alive!
    }

    if(!someoneAlive) // whoops, everyone is dead, Game Over!
    {
      // TODO Actual Game Over Code
      SetBattleState(Idle);
      GameStateManager::SetState(GameStates::Titlescreen);
      _battleMenu.ResetMenu();
    }

    bool enemyAlive(false); // Pretend every enemy is dead...
    for(auto& enemy : _enemies)
    {
      enemy.ResetDamageDisplay();
      enemy.CheckIfDead();
      enemyAlive |= !enemy.IsDead(); // ...until proven otherwise.
    }

    if(!enemyAlive) // FUCK YEAH, WE KILLED THEM FUCKERS!    
      EndBattle();

    return;
  }

  if(_frameCounter > 1)
  {
    for(size_t i = 0; i < _playerRow.size(); ++i)
    {
      _playerRow[i].CurrentHP() -= _charHPStep[i];
      _playerRow[i].Graphics().UpdateHP();
    }
    return;
  }
  _currentAttacker->UseMP(_targetInfo.Spell->GetMPCost(*_currentAttacker));
  bool targetIsEnemy(TargetIsEnemy());

  float charHPBefore[4];
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    charHPBefore[i] = _playerRow[i].CurrentHP();
  }

  TargetInfo::TargetType targetType(_targetInfo.Spell->GetTargetType());
  if(targetType == TargetInfo::Single)
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_targetInfo.Target);
  else if(targetType == TargetInfo::Self)
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_currentAttacker);
  else if(targetType == TargetInfo::Allies || targetType == TargetInfo::Enemies)
  {
    bool attackerIsEnemy(AttackerIsEnemy());
    bool targetIsPlayer((attackerIsEnemy && targetType != TargetInfo::Allies) ||
                        (!attackerIsEnemy && targetType == TargetInfo::Allies));
    for(size_t i = 0; i < (targetIsPlayer ? _playerRow.size() :
                           _enemies.size()); ++i)
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           targetIsPlayer ? _playerRow[i] :
                                                            _enemies[i]);
  }
  else if(_targetInfo.Spell->GetTargetType() == TargetInfo::Decaying)
  {
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_targetInfo.Target);

    size_t attackerIndex = 0;
    for(;attackerIndex < (targetIsEnemy ? _enemies.size() :
                          _playerRow.size()) &&
        (_enemyTurn ?
         &_playerRow[attackerIndex] :
         &_enemies[attackerIndex]) != _targetInfo.Target;
        ++attackerIndex); //This loop has no body intentionally!!!!
    for(int i = attackerIndex - 1, mod = 2; i >= 0; --i, ++mod)
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           targetIsEnemy ? _enemies[i] :
                                                           _playerRow[i], mod);

    for(size_t i = attackerIndex + 1, mod = 2;
        i < (targetIsEnemy ? _enemies.size() : _playerRow.size());
        ++i, ++mod)
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           targetIsEnemy ? _enemies[i] :
                                                           _playerRow[i], mod);
  }
  _enemyTurn = false;
  if(TargetIsEnemy())
    for(auto& enemy : _enemies)
      enemy.Graphics().UpdateHP();

  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _charHPShouldHave[i] = _playerRow[i].CurrentHP();
    _charHPStep[i] = (charHPBefore[i] - _playerRow[i].CurrentHP())
        / ConsequenceFrames;
    _playerRow[i].CurrentHP() = charHPBefore[i] - _charHPStep[i];
    _playerRow[i].Graphics().UpdateHP();
    _playerRow[i].Graphics().UpdateMP();
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
    _enemies[2].Graphics().DrawBattleSprite(renderTarget);
  }

  // CharSprite infront of enemies, but behind CharFrames
  for(size_t i = 0; i < _playerRow.size() && _battleState == BattleMenu
      && _battleMenu.GetMenuState() != BattleMenu::TargetSelection; ++i)
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

  for(auto& enemy : _enemies)
    enemy.Graphics().DrawDamageDone(renderTarget);
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
    _enemies[i].InitializeCharGraphics();
    _enemies[i].Graphics().SetBattleSpritePosition(positions[i]);
  }
}

void Battle::GenerateEnemies(int level, int bossID)
{
  typedef boost::random::uniform_int_distribution<> IntGenerator;
  if(bossID != 0)
  {
    SetupBossBattle(level, bossID);
    return;
  }

  IntGenerator selectEnemyCount(3, 4);
  int enemyCount(selectEnemyCount(_rng));
  IntGenerator selectEnemy(0, MaxEnemyID);
  for(int i = 0; i < enemyCount; ++i)
  {
    sf::String enemyName("Enemy" + std::to_string(selectEnemy(_rng)));
    _enemies.push_back(Character());
    _enemies[i] = Character(enemyName);
    Character& enemy = _enemies[i];
    /* TODO Actual enemy stat generation,
     * taking Sakuya for now since she's pretty balanced */
    enemy.GetStats() = Stats::_baseStats["Sakuya"];

    // Lets boost the base stats, since enemy should be STRONK!
    enemy.CurrentMP() = std::numeric_limits<float>::max();    
    enemy.LvlUp(level);
    Stats::BaseStatMap& bs = enemy.GetStats().BaseStats;
    bs[HP][0] *= EnemyHPMod;
    for(int j = 1; j < 9; ++j)
      bs[(BaseStat)j][0] *= EnemyBaseMod;
    enemy.CurrentHP() = enemy.GetStats().GetTotalBaseStat(HP);
    enemy.InitializeCharGraphics();
    enemy.Graphics().UpdateHP();
    enemy.Graphics().UpdateMP();
  }
}

void Battle::SetupBossBattle(int level, int bossID)
{
  // TODO Boss Stat Generation
}

void Battle::EndBattle()
{
  SetBattleState(Idle);
  GameStateManager::SetState(GameStates::Ingame);
  _battleMenu.ResetMenu();
  int xpAwarded(0);
  for(auto& enemy : _enemies)
  {
    xpAwarded += enemy.IsConvinced() ? XPPerConvincedEnemy : XPPerEnemy;
  }

  if(_isBossfight)
    xpAwarded += _enemies[0].IsConvinced() ? XPFromConvincedBoss : XPFromBoss;

  for(auto& chara : _playerRow)
  {
    chara.GetStats().ReduceBuffEffectiveness(10);
  }

  Party::AddExperience(xpAwarded);
}

bool Battle::TargetIsEnemy()
{
  for(auto& enemy : _currentInstance->_enemies)
  {
    if(&enemy == _currentInstance->_targetInfo.Target)
      return true;
  }
  return false;
}

bool Battle::AttackerIsEnemy()
{
  for(auto& enemy : _currentInstance->_enemies)
  {
    if(&enemy == _currentInstance->_currentAttacker)
      return true;
  }
  return false;
}

Battle* Battle::GetInstance()
{
  return _currentInstance;
}
}
