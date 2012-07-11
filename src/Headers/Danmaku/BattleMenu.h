#pragma once
#include <SFML/System.hpp>
#include "BlackDragonEngine/Menu.h"

namespace Danmaku
{
class Battle;

class BattleMenu : public BlackDragonEngine::Menu
{
public:
  BattleMenu(Battle& battle);
  void Update();
  void Draw(sf::RenderTarget& renderTarget);
  void SelectMenuItem();

private:
  sf::String const Attack;
  sf::String const Spell;
  sf::String const Defend;
  sf::String const Switch;
  sf::String const Convince;

  enum BMenuStates
  {
    ActionSelect,
    TargetSelection,
    SpellSelect,
    SelectCharToSwitch,
    SelectCharToSwitchWith
  } _menuState;

  Battle& _battle;
};
}
