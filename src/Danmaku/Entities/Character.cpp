#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/Spells.h"

namespace Danmaku
{

using namespace BlackDragonEngine;
Character::Character()
  : Character("Reimu")
{
}

Character::Character(sf::String name)
  : _name(name), _stats(), _turnCounter(0), _spellList(), _currentHP(0),
    _currentMP(0), _charFrame()
{
  // TODO Stat Generation
  _stats.HP[0] = 5000.f;
  _currentHP = _stats.HP[0];
  _currentMP = 147;
  _stats.MP[0] = 250;
  _stats.SPD[0] = 100.f;
  _spellList.push_back(&Spells::PlaceHolder);
}


void Character::InitializeCharFrame()
{
  _charFrame = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
}

bool Character::UpdateTurnCounter()
{
  _turnCounter += _stats.SPD[0] / 30.f;
  if(_turnCounter >= TimeToAction)
  {
    _turnCounter = 0.f;    
  }
  _charFrame.UpdateSPD();

  return _turnCounter == 0.f;
}

float& Character::GetCurrentHP()
{
  return _currentHP;
}

float& Character::GetCurrentMP()
{
  return _currentMP;
}

Stats& Character::GetStats()
{
  return _stats;
}

TargetInfo Character::AIBattleMenu(CharVec& targetRow)
{
  // TODO Actual AI code
  TargetInfo targetInfo;
  targetInfo.TargetType = TargetInfo::Single;
  targetInfo.Target = &targetRow[0];
  targetInfo.Spell = _spellList[0];
  return targetInfo;
}
}

