#include <ctime>
#include <limits>
#include <boost/random.hpp>
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
  : _name(name),
    _displayName((name.find("Enemy") == sf::String::InvalidPos) ?
                   GetRandomName() : name),
    _stats(), _turnCounter(0), _spellList(), _currentHP(0),
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
  bool result(false);
  _turnCounter += _stats.SPD[0] / 30.f;
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

TargetInfo Character::AIBattleMenu(CharVec& targetRow)
{
  // TODO Actual AI code
  TargetInfo targetInfo;
  targetInfo.TargetType = TargetInfo::Single;
  targetInfo.Target = &targetRow[0];
  targetInfo.Spell = _spellList[0];
  return targetInfo;
}

sf::String Character::GetRandomName()
{
  typedef boost::random::uniform_int_distribution<> IntGenerator;
  typedef boost::random::mt19937 RandomSeed;
  using namespace std;

  RandomSeed rng(time(0));
  IntGenerator generator(1,16953);

  fstream nameFile("content/etc/CatNames.txt");
  GoToLine(nameFile, generator(rng));

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

