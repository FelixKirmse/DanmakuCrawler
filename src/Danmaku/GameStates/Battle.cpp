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
float const Battle::EnemyHPMod = 2.f;
float const Battle::EnemyBaseMod = .75f;

Battle::Battle()
  : _battleState(Idle), _enemies(), _playerRow(Party::GetFrontRow()),
    _playerBattleParty(Party::GetBackSeat()), _currentAttacker(0),
    _enemyLeftOff(0), _playerLeftOff(0), _frameCounter(0), _enemyTurn(false),
    _battleMenu(*this), _threeLayout(), _fourLayout(), _charHPStep(),
    _charHPShouldHave(), _rng(time(0))
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

void Battle::SetTargetInfo(TargetInfo targetInfo)
{
  _targetInfo = targetInfo;
}

void Battle::SetBattleState(Battle::BattleState battleState)
{
  _battleState = battleState;
}

Battle::CharVec &Battle::GetEnemies()
{
  return _enemies;
}

Party::FrontRow& Battle::GetFrontRow()
{
  return _playerRow;
}

void Battle::StartBattle(int level, int bossID)
{
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
      _battleState = BattleMenu;
      _playerLeftOff = i;
      _currentAttacker = &_playerRow[i];
      _battleMenu.SetCurrentAttacker(_currentAttacker);
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
      _enemyTurn = true;
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
    _battleMenu.ResetMenu();
    _battleState = Idle;
    _frameCounter = 0;

    bool someoneAlive(false); // Pretend every player is dead...
    for(size_t i = 0; i < _playerRow.size(); ++i)
    {
      someoneAlive |= !_playerRow[i].IsDead(); // ...until we find someone alive!
    }

    if(!someoneAlive) // whoops, everyone is dead, Game Over!
    {
      // TODO Actual Game Over Code
      _battleState = Idle;
      GameStateManager::SetState(GameStates::Ingame);
      _battleMenu.ResetMenu();
    }

    bool enemyAlive(false); // Pretend every enemy is dead...
    for(size_t i = 0; i < _enemies.size(); ++i)
    {
      enemyAlive |= !_enemies[i].IsDead(); // ...until proven otherwise.
    }

    if(!enemyAlive) // FUCK YEAH, WE KILLED THEM FUCKERS!
    {
      // TODO Actual winning code
      _battleState = Idle;
      GameStateManager::SetState(GameStates::Ingame);
      _battleMenu.ResetMenu();
    }

    for(size_t i = 0; i < _playerRow.size(); ++i)
    {
      _playerRow[i].CurrentHP() = _charHPShouldHave[i];
      _playerRow[i].Graphics().UpdateHP();
    }
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

  float charHPBefore[4];
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    charHPBefore[i] = _playerRow[i].CurrentHP();
  }

  if(_targetInfo.Spell->GetTargetType() == TargetInfo::Single)
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_targetInfo.Target);

  if(_targetInfo.Spell->GetTargetType() == TargetInfo::All)
  {
    for(size_t i = 0; i < (_enemyTurn ? _playerRow.size() : _enemies.size());
        ++i)
    {
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           (_enemyTurn ?
                                              _playerRow[i] : _enemies[i]));
    }
  }

  if(_targetInfo.Spell->GetTargetType() == TargetInfo::Decaying)
  {
    _targetInfo.Spell->DamageCalculation(*_currentAttacker, *_targetInfo.Target);
    size_t attackerIndex = 0;
    for(;attackerIndex < (_enemyTurn ? _playerRow.size() : _enemies.size()) &&
        (_enemyTurn ?
         &_playerRow[attackerIndex] :
         &_enemies[attackerIndex]) != _targetInfo.Target;
        ++attackerIndex); //This loop has no body intentionally!!!!
    for(int i = attackerIndex - 1, mod = 2; i >= 0; --i, ++mod)
    {
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           (_enemyTurn ?
                                              _playerRow[i] : _enemies[i]),
                                           mod);
    }

    for(size_t i = attackerIndex + 1, mod = 2;
        i < (_enemyTurn ? _playerRow.size() : _enemies.size());
        ++i, ++mod)
    {
      _targetInfo.Spell->DamageCalculation(*_currentAttacker,
                                           (_enemyTurn ?
                                              _playerRow[i] : _enemies[i]),
                                           mod);
    }

    _enemyTurn = false;
  }

  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _charHPShouldHave[i] = _playerRow[i].CurrentHP();
    _charHPStep[i] = (charHPBefore[i] - _playerRow[i].CurrentHP()) / 45.f;
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
    Stats::BaseStatMap& bs = enemy.GetStats().BaseStats;
    bs[HP][0] *= EnemyHPMod;
    for(int j = 1; j < 9; ++j)
      bs[(BaseStat)j][0] *= EnemyBaseMod;
    enemy.GetStats().LvlUp(0, 100); // TODO DELETE
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
}
