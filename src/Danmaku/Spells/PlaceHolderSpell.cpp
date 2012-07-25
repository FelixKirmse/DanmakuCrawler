#include "Danmaku/Spells/PlaceHolderSpell.h"
#include "Danmaku/Character.h"
namespace Danmaku
{
void PlaceHolderSpell::Cast()
{
}

void PlaceHolderSpell::CastUpdate()
{
}

void PlaceHolderSpell::DamageCalculation(Character& attacker,
                                         Character& defender,
                                         float mod)
{
  float damage = 2.f * attacker.GetStats().GetTotalBaseStat(AD) - defender.GetStats().GetTotalBaseStat(DEF);
  defender.CurrentHP() -= (damage > 0) ? damage : 1;
}

TargetInfo::TargetTypes PlaceHolderSpell::GetTargetType()
{
  return TargetInfo::Single;
}

}
