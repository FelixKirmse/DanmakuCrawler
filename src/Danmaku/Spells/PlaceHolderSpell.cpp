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
  defender.CurrentHP() -= 1000.f * 1/mod;
}

TargetInfo::TargetTypes PlaceHolderSpell::GetTargetType()
{
  return TargetInfo::All;
}

}
