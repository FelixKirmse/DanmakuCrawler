#include <ctime>
#include <limits>
#include <string>
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
    _currentMP(0), _graphics(), _dead(false), _level(1),
    _poisoned(false), _poisonDamage(0), _paralyzed(false), _paralyzeStrength(0),
    _paralyzeCounter(0), _silenced(false), _silenceStrength(0)
{  
  AssignSpells();

  if(_displayName == _name)
    _stats = Stats::_baseStats[_name.toAnsiString()];
  _currentHP = _stats.GetTotalBaseStat(HP);
  _currentMP = _stats.GetTotalBaseStat(MP);
}


void Character::InitializeCharGraphics()
{
  _graphics = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
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
  _graphics.UpdateSPD(result);

  if(_poisoned)
    TakeTrueDamage(_poisonDamage);

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
  return _graphics;
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
  IntGenerator evaRoll(0,99);
  int evaChance = _stats.GetTotalBaseStat(EVA);
  bool attackEvaded = evaRoll(_rng) < evaChance;
  if(attackEvaded && _stats.EVAType == Stats::Dodge)
  {
    _graphics.SetDamageDone("Dodged!!", false);
    return;
  }
  value /= attackEvaded ? 2.f : 1.f;
  sf::String addendum(attackEvaded ? ", Blocked!!" : "");
  _graphics.SetDamageDone(std::to_string((int) value) + addendum, false);
  TakeTrueDamage(value);
}

void Character::TakeTrueDamage(float value)
{
  _currentHP -= (value > 0.f) ? value : 0.f;
  _currentHP = (_currentHP < 0.f) ? 0.f : _currentHP;

  if(_currentHP >= 0.f)
    return;
  _graphics.UpdateHP();
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
  _graphics.SetDamageDone(std::to_string((int)value), true);
  _currentHP += value;
  _currentHP = (_currentHP > _stats.GetTotalBaseStat(HP)) ?
        _stats.GetTotalBaseStat(HP) : _currentHP;
}

Character::SpellList& Character::GetSpells()
{
  return _spellList;
}

void Character::CheckIfDead()
{
  if((int)_currentHP > 0)
    return;

  _dead = true;
  _graphics.SetDeadSprites();
}

void Character::ApplyPoison(int damage)
{
  _poisoned = true;
  _poisonDamage = damage;
}

void Character::ApplyPAR(int strength)
{
  _paralyzed = true;
  _paralyzeStrength = strength;
  _paralyzeCounter = TimeToAction;
}

void Character::ApplySIL(int strength)
{
  _silenced = true;
  _silenceStrength = strength;
}

TargetInfo Character::AIBattleMenu(FrontRow& targetRow)
{  
  TargetInfo targetInfo;

  IntGenerator spellSelect(0, _spellList.size() - 1);
  targetInfo.Spell = _spellList[spellSelect(_rng)];
  targetInfo.Target = NULL;

  TargetInfo::TargetType targetType = targetInfo.Spell->GetTargetType();
  if(targetType != TargetInfo::Single && targetType != TargetInfo::Decaying)
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

void Character::AssignSpells()
{
  _spellList.push_back(Spells::GetSpell("Attack"));
  _spellList.push_back(Spells::GetSpell("Defend"));
  #include "CharSpells.inc"
  if(_name == _displayName)
    return;
  //TODO Enemy Spell Generation
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
  _graphics = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
  return *this;
}
}

