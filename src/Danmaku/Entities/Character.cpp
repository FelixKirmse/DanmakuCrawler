#include <ctime>
#include <limits>
#include <string>
#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/Spells.h"


namespace Danmaku
{

Character::RandomSeed Character::_rng(time(0));
int const Character::XPRequiredForLvlUp(2000);
unsigned long long Character::TimeToAction(300);
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
    _currentMP(0), _graphics(), _dead(false), _level(0), _xpRequired(0),
    _poisoned(false), _poisonDamage(0), _paralyzed(false), _paralyzeStrength(0),
    _paralyzeCounter(0), _silenced(false), _silenceStrength(0),
    _convinced(false), _isEnemy(false)
{  
  InitializeCharGraphics();
  AssignSpells();

  if(_displayName == _name)
  {
    _stats = Stats::_baseStats[_name.toAnsiString()];
    _xpRequired = (float)XPRequiredForLvlUp * _stats.XPMultiplier;
  }
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

  int timeStep = _stats.GetTotalBaseStat(SPD);
  if(_paralyzed)
  {
    _paralyzeCounter -= timeStep;
    if(_paralyzeCounter <= 0)
    {
      _paralyzeStrength *= .66f;
      _paralyzed = _stats.TryToApplyDebuff(PAR, _paralyzeStrength);
    }
    return false;
  }

  bool result(false);
  _turnCounter += timeStep;
  if(_turnCounter >= TimeToAction)
  {
    UseMP(-10.f);
    _turnCounter -= TimeToAction;
    result = true;
    _stats.ReduceBuffEffectiveness();
    if(_silenced)
    {
      _silenceStrength *= .66f;
      _silenced = _stats.TryToApplyDebuff(SIL, _silenceStrength);
    }
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

unsigned long long &Character::TurnCounter()
{
  return _turnCounter;
}

sf::String const& Character::GetDisplayName() const
{
  return _displayName;
}

const sf::String &Character::GetInternalName() const
{
  return _name;
}

bool Character::IsDead()
{
  return _dead;
}

void Character::SetDead(bool dead)
{
  _dead = dead;
}

void Character::TakeDamage(float value)
{
  if(value < 0.f)
    value = 0.f;
  IntGenerator evaRoll(0,99);
  int evaChance =  _stats.GetEVAChance(_level);
  bool attackEvaded = evaRoll(_rng) < evaChance;
  if(attackEvaded && _stats.EVAType == Stats::Dodge)
  {
    _graphics.SetDamageDone(0.f, false, false, true);
    return;
  }
  value /= attackEvaded ? 2.f : 1.f;
  TakeTrueDamage(value, attackEvaded);
}

void Character::TakeTrueDamage(float value, bool blocked)
{  
  _graphics.SetDamageDone(value, false, blocked);

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
  _graphics.UpdateMP();
}

void Character::Heal(float value)
{
  _graphics.SetDamageDone(value, true);
  _currentHP += value;
  _currentHP = (_currentHP > _stats.GetTotalBaseStat(HP)) ?
        _stats.GetTotalBaseStat(HP) : _currentHP;
  _graphics.UpdateHP();
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

bool Character::IsSilenced()
{
  return _silenced;
}

bool Character::IsPoisoned()
{
  return _poisoned;
}

void Character::ResetDamageDisplay()
{
  _graphics.ResetDamage();
}

void Character::LvlUp()
{
  if(_displayName == "Dead")
    return;

  long totalXP = Party::GetInstance().GetExperience();
  long currentLevelXP = _level * _xpRequired;
  long difference = totalXP - currentLevelXP;

  while(difference > _xpRequired)
  {
    _stats.LvlUp(_level, 1);
    ++_level;
    difference -= _xpRequired;
  }

  Heal(_stats.GetTotalBaseStat(HP));
  _graphics.ResetDamage();
  _graphics.UpdateMP();
}

void Character::LvlUp(int amount)
{
  _stats.LvlUp(_level, amount);
  _level += amount;
}

int Character::GetLvl()
{
  return _level;
}

void Character::StartBattle()
{
}

void Character::ApplyPoison(int damage, int level)
{
  _poisoned = true;
  _poisonDamage = (damage/100) * level;
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

void Character::RemoveDebuffs()
{
  _silenced = false;
  _paralyzed = false;
  _poisoned = false;
}

bool Character::IsConvinced()
{
  return _convinced;
}

bool &Character::IsEnemy()
{
  return _isEnemy;
}

TargetInfo Character::AIBattleMenu(Party::FrontRow& targetRow)
{  
  TargetInfo targetInfo;

  IntGenerator spellSelect(2, _spellList.size() - 1); // TODO Change to 0
  targetInfo.Spell = _spellList[spellSelect(_rng)];
  targetInfo.Target = NULL;

  TargetInfo::TargetType targetType = targetInfo.Spell->GetTargetType();
  if(targetType == TargetInfo::Allies || targetType == TargetInfo::Enemies)
    return targetInfo;


  if(targetType == TargetInfo::Self)
  {
    targetInfo.Target = this;
    return targetInfo;
  }
  IntGenerator targetSelect(0,99);
  do
  {
    int target = targetSelect(_rng);
    /* 60% to attack main tank
     * 30% to attack secondary tank
     * 5% each to attack back row
     */
    targetInfo.Target = targetRow[(target < 60) ?
          0 : (target < 90) ?
            1 : (target < 95) ?
              2 : 3];
  }while(targetInfo.Target->IsDead());

  return targetInfo;
}

sf::String Character::GetRandomName()
{  
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
  //TODO Proper Enemy Spell Generation
  IntGenerator spellCountRoll(3,5);
  int spellCount = spellCountRoll(_rng);

  for(int i = 0; i < spellCount; ++i)
  {
    _spellList.push_back(Spells::GetRandomSpell());
  }
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
  _xpRequired = source._xpRequired;
  _graphics = CharGraphics(sf::Vector2f(0.f, 0.f), _name, this);
  return *this;
}

void Character::EndBattle()
{
  UseMP(-50.f);
}
}

