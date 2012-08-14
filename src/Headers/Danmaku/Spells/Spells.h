#pragma once
#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/random.hpp>
#include "Danmaku/Spells/Spell.h"

namespace Danmaku
{
class Spells
{
public:
  typedef boost::random::mt19937 RandomSeed;

  static void InitializeSpells();
  static Spell* GetSpell(int id);
  static Spell* GetSpell(sf::String name);

private:
  static std::vector<Spell> _spells;
  static boost::unordered::unordered_map<std::string, int> _nameIndexMap;
  static RandomSeed _rng;
};
}
