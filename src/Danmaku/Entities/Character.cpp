#include <ctime>
#include <limits>
#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/Spells.h"

namespace Danmaku
{

Character::RandomSeed Character::_rng(time(0));

using namespace BlackDragonEngine;
Character::Character()
  : Character("Reimu")
{
}

Character::Character(sf::String name)
  : _name(name),
    _displayName((name.find("Enemy") == sf::String::InvalidPos) ?
                   _name : GetRandomName()),
    _stats(), _turnCounter(0), _spellList(), _currentHP(0),
    _currentMP(0), _charFrame(), _dead(false)
{
  // TODO Stat Generation
  _stats.BaseStats[HP][0] = 10000.f;
  _currentHP = _stats.BaseStats[HP][0];
  _currentMP = 147;
  _stats.BaseStats[MP][0] = 250;
  _stats.BaseStats[SPD][0] = 100.f;
  _spellList.push_back(&Spells::PlaceHolder);
}


void Character::InitializeCharFrame()
{
  _charFrame = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
}

bool Character::UpdateTurnCounter()
{
  if(_dead)
    return false;

  bool result(false);
  _turnCounter += _stats.BaseStats[SPD][0] / 30.f;
  if(_turnCounter >= TimeToAction)
  {
    _turnCounter -= TimeToAction;
    result = true;
  }
  _charFrame.UpdateSPD(result);

  return result;
}

float& Character::CurrentHP()
{
  return _currentHP;
}

float& Character::CurrentMP()
{
  return _currentMP;
}

Stats& Character::GetStats()
{
  return _stats;
}

CharGraphics& Character::Graphics()
{
  return _charFrame;
}

int& Character::TurnCounter()
{
  return _turnCounter;
}

sf::String const& Character::GetDisplayName()
{
  return _displayName;
}

bool& Character::IsDead()
{
  return _dead;
}

TargetInfo Character::AIBattleMenu(CharVec& targetRow)
{
  TargetInfo targetInfo;

  // TODO Actual Spell Selection code
  targetInfo.Spell = _spellList[0];
  targetInfo.TargetType = targetInfo.Spell->GetTargetType();
  targetInfo.Target = NULL;

  if(targetInfo.TargetType == TargetInfo::All)
    return targetInfo;

  typedef boost::random::uniform_int_distribution<> IntGenerator;
  IntGenerator targetSelect(0,99);

  do
  {
    int target = targetSelect(_rng);
    /* 60% to attack main tank
     * 30% to attack secondary tank
     * 5% each to attack back row
     */
    targetInfo.Target = &targetRow[(target < 60) ?
          0 : (target < 90) ?
            1 : (target < 95) ?
              2 : 3];
  }while(targetInfo.Target->IsDead());

  return targetInfo;
}

sf::String Character::GetRandomName()
{
  typedef boost::random::uniform_int_distribution<> IntGenerator;
  using namespace std;
  IntGenerator generator(1,16953);

  fstream nameFile("content/etc/CatNames.txt");
  GoToLine(nameFile, generator(_rng));

  string stdName;
  nameFile >> stdName;
  return sf::String(stdName);
}

void Character::GoToLine(std::fstream& file, size_t num)
{
  file.seekg(std::ios::beg);
  for(size_t i = 0; i < num - 1; ++i)
  {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

}

