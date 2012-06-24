#include "Danmaku/Spells/PlaceHolderSpell.h"

namespace Danmaku
{
void PlaceHolderSpell::Cast()
{
}

void PlaceHolderSpell::CastUpdate()
{
}

void PlaceHolderSpell::DamageCalculation(Character& player,
                                         Character& enemy,
                                         float specialModifier)
{
  enemy.GetCurrentHP() -= 500.f;
}
}
