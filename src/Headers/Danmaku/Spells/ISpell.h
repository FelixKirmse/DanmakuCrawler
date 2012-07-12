#pragma once
#include "Danmaku/Character.h"

namespace Danmaku
{
class ISpell
{
public:
  virtual ~ISpell() {}
  virtual void Cast() = 0;
  virtual void CastUpdate() = 0;
  virtual void DamageCalculation(Character& attacker,
                                 Character& defender,
                                 float specialModifier = 0.f) = 0;
};
}