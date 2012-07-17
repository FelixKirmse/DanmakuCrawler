#pragma once
#include <fstream>
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
  enum TargetTypes
  {
    Single,
    All,
    Decaying
  } TargetType;
  Character* Target;
  ISpell* Spell;
};

class Character
{
public:  
  typedef std::vector<ISpell*> SpellList;
  typedef std::vector<Character> CharVec;
  typedef boost::random::mt19937 RandomSeed;

  Character();
  Character(sf::String name);

  void InitializeCharFrame();
  bool UpdateTurnCounter();
  float& CurrentHP();
  float& CurrentMP();
  Stats& GetStats();
  CharGraphics& Graphics();
  int& TurnCounter();
  sf::String const& GetDisplayName();
  bool IsDead();

  TargetInfo AIBattleMenu(CharVec& targetRow);

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
  CharGraphics _charFrame;
  bool _dead;

  static RandomSeed _rng;
};
}
