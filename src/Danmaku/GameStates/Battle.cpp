#include <string>
#include <ctime>
#include <limits>
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Battle.h"
#include "Danmaku/Spells/ISpell.h"
#include "boost/format.hpp"
#include "Danmaku/Stats.h"
#include "Danmaku/StatOverview.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/CharSwitch.h"


namespace Danmaku
{
Battle* Battle::_currentInstance;
size_t Battle::MaxEnemyID;

sf::Vector2f const Battle::FrameContainerStart(200.f, 380.f);
int const Battle::FrameContainerOffset(110);
float const Battle::EnemyHPMod(5.f);
float const Battle::EnemyBaseMod(.4f);

Battle::Battle()
  : _enemies(),
    _party(Party::GetInstance()),
    _playerRow(_party.GetFrontRow()),
    _currentAttacker(0),
    _enemyTurn(false),
    _idleState(_enemies), _battleMenu(*this), _actionState(),
    _consequenceState(_enemies), _gameOverState(), _battleWonState(_enemies),
    _battleState(&_idleState),
    _threeLayout(), _fourLayout(),
    _rng(time(0)), _queuedState(&_idleState), _stateChanged(false)
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
  if(_stateChanged)
  {
    _battleState = _queuedState;
    _stateChanged = false;
  }
  _battleState->Update(*this);
  for(auto* chara : _playerRow)
    chara->Graphics().UpdateHP();
  return false;
}

bool Battle::DrawCondition()
{
  return GameStateManager::GetState() == GameStates::Battle;
}

void Battle::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
  if(_enemies.size() == 4)
  {
    _enemies[2]->Graphics().DrawBattleSprite(renderTarget);
    _enemies[0]->Graphics().DrawBattleSprite(renderTarget);
    _enemies[1]->Graphics().DrawBattleSprite(renderTarget);
    _enemies[3]->Graphics().DrawBattleSprite(renderTarget);
  }
  else
  {
    _enemies[1]->Graphics().DrawBattleSprite(renderTarget);
    _enemies[0]->Graphics().DrawBattleSprite(renderTarget);
    _enemies[2]->Graphics().DrawBattleSprite(renderTarget);
  }



  // CharSprite infront of enemies, but behind CharFrames
  for(size_t i = 0; i < _playerRow.size() && _battleState == &_battleMenu
      && _battleMenu.GetMenuState() != BattleMenu::TargetSelection; ++i)
  {
    _playerRow[i]->Graphics().DrawCharSprite(renderTarget);
  }

  // StatScreen infront of Charsprite
  if(_battleState == &_battleMenu &&
     _battleMenu.GetMenuState() == BattleMenu::ActionSelect)
    StatOverview::GetInstance().Draw(renderTarget);

  // CharFrames ontop
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i]->Graphics().Draw(renderTarget);
  }

  _battleState->Draw(*this, renderTarget);
}

void Battle::SetTargetInfo(TargetInfo targetInfo)
{
  _targetInfo = targetInfo;
}

Battle::CharVec& Battle::GetEnemies()
{
  return _enemies;
}

Party::FrontRow& Battle::GetFrontRow()
{
  return _playerRow;
}

void Battle::SetIdle()
{
  _queuedState = &_idleState;
  _stateChanged = true;
}

void Battle::ShowBattleMenu()
{
  _battleMenu.ResetMenu();
  _queuedState = &_battleMenu;
  _stateChanged = true;
}

void Battle::PerformAction()
{
  _queuedState = &_actionState;
  _stateChanged = true;
}

void Battle::ShowConsequences()
{
  _queuedState = &_consequenceState;
  _stateChanged = true;
}

void Battle::GameOver()
{
  _queuedState = &_gameOverState;
  _stateChanged = true;
}

void Battle::BattleWon()
{
  _queuedState = &_battleWonState;
  _stateChanged = true;
}

void Battle::StartBattle(int level, int bossID)
{
  Character::TimeToAction = _currentInstance->GetAvgSPD();


  _currentInstance->_isBossfight = bossID != 0;
  GameStateManager::SetState(GameStates::Battle);
  // TODO enemy generation code
  _currentInstance->_enemies.clear();

  _currentInstance->GenerateEnemies(level, bossID);

  _currentInstance->SetInitialSPD(_currentInstance->_enemies);
  _currentInstance->SetInitialSPD(_currentInstance->_playerRow);
  _currentInstance->SetInitialSPD(_currentInstance->_party.GetAvailableCharacters());
  _currentInstance->ArrangeCharFrames(bossID);
}

unsigned long long Battle::GetAvgSPD()
{
  unsigned long long spdTotal(0);
  int charCount(0);
  for(auto* chara : _enemies)
  {
    spdTotal += chara->GetStats().GetTotalBaseStat(SPD);
    ++charCount;
  }
  for(auto* chara : _playerRow)
  {
    if(chara->IsDead())
      continue;
    spdTotal += chara->GetStats().GetTotalBaseStat(SPD);
    ++charCount;
  }
  for(auto* chara : _party.GetAvailableCharacters())
  {
    if(chara->IsDead())
      continue;
    spdTotal += chara->GetStats().GetTotalBaseStat(SPD);
    ++charCount;
  }
  return (float)spdTotal / charCount * 90.f;
}


void Battle::ArrangeCharFrames(int bossID)
{
  for(size_t i = 0; i < _playerRow.size(); ++i)
  {
    _playerRow[i]->Graphics().Reposition(FrameContainerStart.x
                                         + i * FrameContainerOffset,
                                         FrameContainerStart.y);
    _playerRow[i]->StartBattle();
  }

  if(bossID != 0)
  {
    // TODO Boss Arrangement
    return;
  }

  VecVec& positions = (_enemies.size() == 3) ? _threeLayout : _fourLayout;
  for(size_t i = 0; i < _enemies.size(); ++i)
  {
    _enemies[i]->IsEnemy() = true;
    _enemies[i]->Graphics().SetBattleSpritePosition(positions[i]);
    _enemies[i]->StartBattle();
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
  _enemies.clear();
  IntGenerator selectEnemy(0, MaxEnemyID);
  for(int i = 0; i < enemyCount; ++i)
  {
    sf::String enemyName("Enemy" + std::to_string(selectEnemy(_rng)));
    _enemies.push_back(new Character(enemyName));
    Character& enemy = *_enemies[i];
    /* TODO Actual enemy stat generation,
     * taking Sakuya for now since she's pretty balanced */
    enemy.GetStats() = Stats::_baseStats["Sakuya"];

    // Lets boost the base stats, since enemy should be STRONK!
    enemy.CurrentMP() = std::numeric_limits<float>::max();
    enemy.LvlUp(level);
    Stats::BaseStatMap& bs = enemy.GetStats().BaseStats;
    bs[HP][0] *= EnemyHPMod;
    for(int j = 1; j < 7; ++j)
      bs[(BaseStat)j][0] *= EnemyBaseMod;
    enemy.CurrentHP() = enemy.GetStats().GetTotalBaseStat(HP);
    enemy.Graphics().UpdateHP();
    enemy.Graphics().UpdateMP();
  }
}

void Battle::SetupBossBattle(int level, int bossID)
{
  // TODO Boss Stat Generation
}


bool Battle::TargetIsEnemy()
{
  for(auto* enemy : _currentInstance->_enemies)
  {
    if(enemy == _currentInstance->_targetInfo.Target)
      return true;
  }
  return false;
}

bool Battle::AttackerIsEnemy()
{
  for(auto* enemy : _currentInstance->_enemies)
  {
    if(enemy == _currentInstance->_currentAttacker)
      return true;
  }
  return false;
}

Battle* Battle::GetInstance()
{
  return _currentInstance;
}

bool Battle::IsBossFight()
{
  return _isBossfight;
}

}
