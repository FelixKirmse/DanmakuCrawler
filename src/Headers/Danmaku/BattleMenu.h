#pragma once
#include <SFML/System.hpp>
#include "BlackDragonEngine/Menu.h"
#include "Danmaku/Character.h"
#include "Danmaku/TargetSelectMenu.h"
#include "Danmaku/SpellSelectMenu.h"
#include "Danmaku/IFinishedNotifier.h"

namespace Danmaku
{
class Battle;
class Character;
class ISpell;
class CharSwitch;

class BattleMenu
    : public BlackDragonEngine::Menu,
      public IFinishedNotifier
{
public:
  enum BMenuState
  {
    ActionSelect,
    TargetSelection,
    SpellSelect,
    SwitchCharacter
  };

  BattleMenu(Battle& battle);
  void Update();
  void Draw(sf::RenderTarget& renderTarget);
  void SelectMenuItem();
  void SetCurrentAttacker(Character* currentAttacker);
  Character* GetCurrentAttacker();
  void SetTarget(Character* target);
  void SetSpell(ISpell* spell);
  BMenuState GetMenuState();
  void SetMenuState(BMenuState newState);
  void ResetMenu();
  void WorkFinished();
  void WorkCancelled();

private:
  sf::String const Attack;
  sf::String const Spell;
  sf::String const Defend;
  sf::String const Switch;
  sf::String const Convince;

  BMenuState _menuState;

  Battle& _battle;
  TargetSelectMenu _targetSelectMenu;
  SpellSelectMenu _spellSelectMenu;
  Character* _currentAttacker;
  TargetInfo _targetInfo;
  CharSwitch& _charSwitch;
};
}
