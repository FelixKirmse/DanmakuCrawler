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
    All,
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
  void UseMP(float value);
  void Heal(float value);
  SpellList& GetSpells();
  void CheckIfDead();

  TargetInfo AIBattleMenu(FrontRow& targetRow);

  Character& operator=(Character const& source);

  int const TimeToAction = 300;

private:
  sf::String GetRandomName();
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

  static RandomSeed _rng;
};
}
