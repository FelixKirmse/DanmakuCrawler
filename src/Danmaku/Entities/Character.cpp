#include <ctime>
#include <limits>
#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/Spells.h"

namespace Danmaku
{

Character::RandomSeed Character::_rng(time(0));
typedef boost::random::uniform_int_distribution<> IntGenerator;

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
  _spellList.push_back(Spells::GetSpell("Attack"));
  _spellList.push_back(Spells::GetSpell("Defend"));

  if(_displayName == _name)
    _stats = Stats::_baseStats[_name.toAnsiString()];
  _currentHP = _stats.GetTotalBaseStat(HP);
  _currentMP = _stats.GetTotalBaseStat(MP);
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
    _stats.ReduceBuffEffectiveness();
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

sf::String const& Character::GetDisplayName() const
{
  return _displayName;
}

bool& Character::IsDead()
{
  return _dead;
}

void Character::TakeDamage(float value)
{
  _currentHP -= (value > 0.f) ? value : 0.f;
  _currentHP = (_currentHP < 0.f) ? 0.f : _currentHP;
}

void Character::UseMP(float value)
{
  _currentMP -= value;
  _currentMP = (_currentMP < 0.f) ?
        0.f : _currentMP > _stats.GetTotalBaseStat(MP) ?
          _stats.GetTotalBaseStat(MP) : _currentMP;
}

void Character::Heal(float value)
{
  _currentHP += value;
  _currentHP = (_currentHP > _stats.GetTotalBaseStat(HP)) ?
        _stats.GetTotalBaseStat(HP) : _currentHP;
}

Character::SpellList& Character::GetSpells()
{
  return _spellList;
}

TargetInfo Character::AIBattleMenu(FrontRow& targetRow)
{  
  TargetInfo targetInfo;

  IntGenerator spellSelect(0, _spellList.size() - 1);
  targetInfo.Spell = _spellList[spellSelect(_rng)];
  targetInfo.Target = NULL;

  if(targetInfo.Spell->GetTargetType() == TargetInfo::All)
    return targetInfo;


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
  IntGenerator generator(1,13874);

  fstream nameFile("content/etc/CatNames.txt");
  GoToLine(nameFile, generator(_rng));

  string stdName;
  getline(nameFile, stdName);
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
}

