#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/Spells.h"

namespace Danmaku
{

using namespace BlackDragonEngine;
Character::Character()
  : Character("Default")
{
}

Character::Character(sf::String name)
  : _name(name),
    _charPortrait(Provider<sf::Texture>::Get("PlaceHolderPortrait")),
    _charBattleSprite(Provider<sf::Texture>::Get("PlaceHolderPortrait")),
    _stats(), _turnCounter(0), _spellList(), _currentHP(0)
{
  // TODO Stat Generation
  _stats.HP[0] = 5000.f;
  _currentHP = _stats.HP[0];
  _stats.SPD[0] = 100.f;
  _spellList.push_back(&Spells::PlaceHolder);
}


bool Character::UpdateTurnCounter()
{
  _turnCounter += _stats.SPD[0] / 30.f;
  if(_turnCounter >= TimeToAction)
  {
    _turnCounter = 0.f;    
  }

  return _turnCounter == 0.f;
}

float& Character::GetCurrentHP()
{
  return _currentHP;
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

