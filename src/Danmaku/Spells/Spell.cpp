#include "Danmaku/Spells/Spell.h"

namespace Danmaku
{
Spell::Spell(sf::String const& name, sf::String const& description,
             TargetInfo::TargetType targetType,
             Spell::DamageFuncType damageCalculation, float mpCost, float postUseGauge)
  : _name(name), _description(description), _targetType(targetType),
    _damageCalculation(damageCalculation), _mpCost(mpCost),
    _postUseTurnCount(postUseGauge)
{
}

void Spell::DamageCalculation(Character& attacker, Character& defender,
                              float mod)
{
  _damageCalculation(attacker, defender, mod);
  attacker.TurnCounter() = attacker.TimeToAction * _postUseTurnCount;
}

TargetInfo::TargetType Spell::GetTargetType()
{
  return _targetType;
}

sf::String const& Spell::GetName()
{
  return _name;
}

sf::String const& Spell::GetDescription()
{
  return _description;
}
float Spell::GetMPCost(Character& caster)
{
  return 100.f * _mpCost;
}
}
