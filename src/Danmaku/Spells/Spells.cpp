#include <ctime>
#include "Danmaku/Spells/Spells.h"
#include "Danmaku/Character.h"
#include "Danmaku/Stats.h"
#include "Danmaku/Party.h"
#include "Danmaku/Battle.h"

namespace Danmaku
{
Party& Spells::_party(Party::GetInstance());
std::vector<Spell> Spells::_spells;
boost::unordered::unordered_map<std::string, int> Spells::_nameIndexMap;
Spells::RandomSeed Spells::_rng(time(0));

typedef boost::random::uniform_int_distribution<> IntGenerator;

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

Spell* Spells::GetRandomSpell()
{
  return &_spells[IntGenerator(4, _spells.size() - 1)(_rng)];
}
}
