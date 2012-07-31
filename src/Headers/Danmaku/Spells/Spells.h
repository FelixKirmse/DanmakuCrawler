#pragma once
#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include "Danmaku/Spells/Spell.h"

namespace Danmaku
{
class Spells
{
public:
  static void InitializeSpells();
  static Spell* GetSpell(int id);
  static Spell* GetSpell(sf::String name);

private:
  static std::vector<Spell> _spells;
  static boost::unordered::unordered_map<std::string, int> _nameIndexMap;
};
}
