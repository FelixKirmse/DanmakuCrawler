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
#include "Danmaku/Party.h"


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
  typedef boost::random::mt19937 RandomSeed;

  Character();
  Character(sf::String name);

  bool UpdateTurnCounter();
  float& CurrentHP();
  float& CurrentMP();
  Stats& GetStats();
  CharGraphics& Graphics();
  unsigned long long& TurnCounter();
  sf::String const& GetDisplayName() const;
  sf::String const& GetInternalName() const;
  bool IsDead();
  void SetDead(bool dead);
  void TakeDamage(float value);
  void TakeTrueDamage(float value, bool blocked = false);
  void UseMP(float value);
  void Heal(float value);
  SpellList& GetSpells();
  void CheckIfDead();
  bool IsSilenced();
  bool IsPoisoned();
  void ResetDamageDisplay();
  void LvlUp(); // For PCs
  void LvlUp(int amount); // For NPCs
  int GetLvl();
  void StartBattle();
  void EndBattle();

  // Status Ailments-Related
  void ApplyPoison(int damage, int level);
  void ApplyPAR(int strength);
  void ApplySIL(int strength);
  void RemoveDebuffs();

  bool IsConvinced();
  bool& IsEnemy();

  TargetInfo AIBattleMenu(Party::FrontRow& targetRow);

  Character& operator=(Character const& source);

  static Character* GenerateCharacter(sf::String const& name = "_");

  static unsigned long long TimeToAction;
  static int const XPRequiredForLvlUp;

private:
  void InitializeCharGraphics();

  sf::String GetRandomName();
  void AssignSpells();
  void GoToLine(std::fstream& file, size_t num);

  sf::String _name;
  sf::String _displayName;
  Stats _stats;
  unsigned long long _turnCounter;
  SpellList _spellList;
  float _currentHP;
  float _currentMP;
  CharGraphics _graphics;
  bool _dead;
  size_t _level;
  long long _xpRequired;

  // Status Ailments-Related
  bool _poisoned;
  int _poisonDamage;
  bool _paralyzed;
  int _paralyzeStrength;
  int _paralyzeCounter;
  bool _silenced;
  int _silenceStrength;

  bool _convinced;
  bool _isEnemy;

  static RandomSeed _rng;
  static float const PlayerDamageTakenMod;
};
}
