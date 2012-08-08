#pragma once
#include <SFML/System.hpp>
#include "Danmaku/Character.h"

namespace Danmaku
{
class ISpell
{
public:
  virtual ~ISpell() {}
  virtual void DamageCalculation(Character& attacker,
                                 Character& defender,
                                 float specialModifier = 1.f) = 0;
  virtual TargetInfo::TargetType GetTargetType() = 0;
  virtual sf::String const& GetName() = 0;
  virtual sf::String const& GetDescription() = 0;
  virtual float GetMPCost(Character& caster) = 0;
};
}
