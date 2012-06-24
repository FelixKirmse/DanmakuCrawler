#pragma once
#include <vector>
#include <memory>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Danmaku/Stats.h"

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
  friend class Battle;
  typedef std::vector<ISpell*> SpellList;
  typedef std::vector<Character> CharVec;

  Character();
  Character(sf::String name);

  bool UpdateTurnCounter();
  float& GetCurrentHP();
  Stats& GetStats(); 

  TargetInfo AIBattleMenu(CharVec &targetRow);

private:
  sf::String _name;
  sf::Texture _charPortrait;
  sf::Texture _charBattleSprite;
  Stats _stats;
  int _turnCounter;
  SpellList _spellList;
  float _currentHP; 

  int const TimeToAction = 300;
};
}
