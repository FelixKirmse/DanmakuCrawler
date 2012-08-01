#pragma once
#include <SFML/System.hpp>
#include "BlackDragonEngine/Menu.h"
#include "Danmaku/Character.h"
#include "Danmaku/TargetSelectMenu.h"

namespace Danmaku
{
class Battle;
class Character;

class BattleMenu : public BlackDragonEngine::Menu
{
public:
  enum BMenuState
  {
    ActionSelect,
    TargetSelection,
    SpellSelect,
    SelectCharToSwitch,
    SelectCharToSwitchWith
  };

  BattleMenu(Battle& battle);
  void Update();
  void Draw(sf::RenderTarget& renderTarget);
  void SelectMenuItem();
  void SetCurrentAttacker(Character* currentAttacker);
  void SetTarget(Character* target);
  BMenuState GetMenuState();
  void SetMenuState(BMenuState newState);
  void ResetMenu();

private:
  sf::String const Attack;
  sf::String const Spell;
  sf::String const Defend;
  sf::String const Switch;
  sf::String const Convince;

  BMenuState _menuState;

  Battle& _battle;
  TargetSelectMenu _targetSelectMenu;
  Character* _currentAttacker;
  TargetInfo _targetInfo;
};
}
