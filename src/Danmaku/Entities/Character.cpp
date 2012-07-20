#include <ctime>
#include <limits>
#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/Spells.h"

#include <fstream>
#include "Danmaku/SerializeUnorderedMap.h"
#include <boost/serialization/array.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace Danmaku
{

Character::RandomSeed Character::_rng(time(0));

using namespace BlackDragonEngine;
Character::Character()
  : Character("Dead")
{
  _dead = true;
}

Character::Character(sf::String name)
  : _name(name),
    _displayName((name.find("Enemy") == sf::String::InvalidPos) ?
                   _name : GetRandomName()),
    _stats(), _turnCounter(0), _spellList(), _currentHP(0),
    _currentMP(0), _charGraphics(), _dead(false), _level(1)
{
  // TODO Stat Generation
  _stats.BaseStats[HP][0] = 10000.f;
  _currentHP = _stats.BaseStats[HP][0];
  _currentMP = 250;
  _stats.BaseStats[MP][0] = 250;
  _stats.BaseStats[SPD][0] = 100.f;
  _spellList.push_back(&Spells::PlaceHolder);
  //SetBaseStats();
}


void Character::InitializeCharGraphics()
{
  _charGraphics = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
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
  _charGraphics.UpdateSPD(result);

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
  return _charGraphics;
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

TargetInfo Character::AIBattleMenu(FrontRow& targetRow)
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

Character& Character::operator=(Character const& source)
{
  _name = source._name;
  _displayName = source._displayName;
  _stats = source._stats;
  _turnCounter = source._turnCounter;
  _spellList = source._spellList;
  _currentHP = source._currentHP;
  _currentMP = source._currentMP;
  _dead = source._dead;
  _level = source._level;
  _charGraphics = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
  return *this;
}

void Character::SetBaseStats()
{
  Stats example;
  example.EVAType = Stats::Block;
  example.BaseStats[HP] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[MP] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[AD] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[MD] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[DEF] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[MR] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[EVA] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[SPD] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.BaseStats[CHA] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };

  example.Masteries[FIR] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[WAT] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[ICE] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[ARC] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[WND] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[HOL] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[DRK] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[GRN] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Masteries[LGT] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };

  example.Resistances[PSN] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Resistances[PAR] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Resistances[SLW] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Resistances[STD] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Resistances[DTH] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };
  example.Resistances[SIL] = { {0.f,1.f,2.f,3.f,4.f,5.f,6.f} };

  boost::unordered::unordered_map<std::string, Stats> nameStatMap;
  nameStatMap["Reimu"] = example;

  std::ofstream ofs("test.txt");
  boost::archive::xml_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(nameStatMap);
}

}

