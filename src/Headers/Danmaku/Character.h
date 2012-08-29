#pragma once
#include <fstream>
#include <array>
#include <vector>
#include <memory>
#include <boost/random.hpp>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Danmaku/Stats.h"
#include "Danmaku/CharGraphics.h"

namespace Danmaku
{
class Character;
class ISpell;
class Battle;

struct TargetInfo
{
  enum TargetType
  {
    Single,
    Self,
    Allies,
    Enemies,
    Decaying
  };

  Character* Target;
  ISpell* Spell;
};

class Character
{
public:  
  typedef std::vector<ISpell*> SpellList;
  typedef std::array<Character, 4> FrontRow;
  typedef boost::random::mt19937 RandomSeed;

  Character();
  Character(sf::String name);

  void InitializeCharGraphics();
  bool UpdateTurnCounter();
  float& CurrentHP();
  float& CurrentMP();
  Stats& GetStats();
  CharGraphics& Graphics();
  int& TurnCounter();
  sf::String const& GetDisplayName() const;
  bool& IsDead();
  void TakeDamage(float value);
  void TakeTrueDamage(float value);
  void UseMP(float value);
  void Heal(float value);
  SpellList& GetSpells();
  void CheckIfDead();
  bool IsSilenced();
  void ResetDamageDisplay();
  void LvlUp(int amount);

  // Status Ailments-Related
  void ApplyPoison(int damage);
  void ApplyPAR(int strength);
  void ApplySIL(int strength);
  void RemoveDebuffs();

  TargetInfo AIBattleMenu(FrontRow& targetRow);

  Character& operator=(Character const& source);

  int const TimeToAction = 300;

private:
  sf::String GetRandomName();
  void AssignSpells();
  void GoToLine(std::fstream& file, size_t num);

  sf::String _name;
  sf::String _displayName;
  Stats _stats;
  int _turnCounter;
  SpellList _spellList;
  float _currentHP;
  float _currentMP;
  CharGraphics _graphics;
  bool _dead;
  size_t _level;

  // Status Ailments-Related
  bool _poisoned;
  int _poisonDamage;
  bool _paralyzed;
  int _paralyzeStrength;
  int _paralyzeCounter;
  bool _silenced;
  int _silenceStrength;

  static RandomSeed _rng;
};
}
