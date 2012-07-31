#include "Danmaku/Spells/Spells.h"
#include "Danmaku/Character.h"
#include "Danmaku/Stats.h"

namespace Danmaku
{
std::vector<Spell> Spells::_spells;
boost::unordered::unordered_map<std::string, int> Spells::_nameIndexMap;

void Spells::InitializeSpells()
{
  _spells = {
              #include "Spells.inc"
            };

  for(size_t i = 0; i < _spells.size(); ++i)
  {
    _nameIndexMap[_spells[i].GetName().toAnsiString()] = i;
  }
}

Spell* Spells::GetSpell(int id)
{
  return &_spells[id];
}

Spell* Spells::GetSpell(sf::String name)
{
  return &_spells[_nameIndexMap[name.toAnsiString()]];
}
}
