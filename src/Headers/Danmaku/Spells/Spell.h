#pragma once
#include <functional>
#include <SFML/System.hpp>
#include "Danmaku/Spells/ISpell.h"
#include "Danmaku/Character.h"

namespace Danmaku
{
class Spell : public ISpell
{
public:
  typedef std::function<void(Character&, Character&, float)> DamageFuncType;

  Spell(sf::String const& name, sf::String const& description,
        TargetInfo::TargetTypes targetType, DamageFuncType damageCalculation,
        float mpCost);

  void DamageCalculation(Character& attacker, Character& defender,
                         float mod);
  TargetInfo::TargetTypes GetTargetType();
  sf::String const& GetName();
  sf::String const& GetDescription();
  float GetMPCost();

private:
  sf::String _name;
  sf::String _description;
  TargetInfo::TargetTypes _targetType;
  DamageFuncType _damageCalculation;
  float _mpCost;
};
}
