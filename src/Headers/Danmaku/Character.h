#pragma once
#include <vector>
#include <memory>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Danmaku/Stats.h"
#include "Danmaku/CharFrame.h"

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
  } TargetType;
  Character* Target;
  ISpell* Spell;
};

class Character
{
public:
  friend class CharFrame;
  friend class Battle;
  typedef std::vector<ISpell*> SpellList;
  typedef std::vector<Character> CharVec;

  Character();
  Character(sf::String name);

  void InitializeCharFrame();
  bool UpdateTurnCounter();
  float& GetCurrentHP();
  float& GetCurrentMP();
  Stats& GetStats();

  TargetInfo AIBattleMenu(CharVec& targetRow);

private:
  sf::String _name;  
  Stats _stats;
  int _turnCounter;
  SpellList _spellList;
  float _currentHP;
  float _currentMP;
  CharFrame _charFrame;

  int const TimeToAction = 300;
};
}
