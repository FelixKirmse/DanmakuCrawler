#pragma once
#include "Danmaku/Spells/ISpell.h"

namespace Danmaku
{
class PlaceHolderSpell : public ISpell
{
public:
  void Cast();
  void CastUpdate();
  void DamageCalculation(Character& attacker,
                         Character& defender,
                         float mod = 1.f);
  TargetInfo::TargetTypes GetTargetType();
};
}
