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
                                         float specialModifier)
{
  defender.CurrentHP() -= 2500.f;
}

TargetInfo::TargetTypes PlaceHolderSpell::GetTargetType()
{
  return TargetInfo::Single;
}

}
