#include "Danmaku/BattleMenu.h"
#include "Danmaku/Battle.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/Character.h"
#include "Danmaku/Spells/ISpell.h"
#include "BlackDragonEngine/MenuItem.h"
#include "Danmaku/CharSwitch.h"
#include "Danmaku/Spells/Spells.h"

namespace Danmaku
{

BattleMenu::BattleMenu(Battle& battle)
  : Attack("Attack"), Spell("Spell"), Defend("Defend"), Switch("Switch"),
    Convince("Convince"), _menuState(ActionSelect), _battle(battle),
    _targetSelectMenu(battle, *this), _spellSelectMenu(this),
    _charSwitch(CharSwitch::GetInstance())
{
  using namespace BlackDragonEngine;
  AddMenuItem(new MenuItem(Attack, FontName, true));
  AddMenuItem(new MenuItem(Spell));
  AddMenuItem(new MenuItem(Defend));
  AddMenuItem(new MenuItem(Switch));
  AddMenuItem(new MenuItem(Convince));
  EnableMouseSelection = false;
  SetPositions(sf::Vector2f(10.f, 408.f), false);
  _charSwitch.SetNotifier(this);
}

void BattleMenu::Update()
{  
  switch(_menuState)
  {
  case ActionSelect:
    BlackDragonEngine::Menu::Update();
    break;

  case TargetSelection:
    _targetSelectMenu.Update();
    break;

   case SpellSelect:
    _spellSelectMenu.Update();
    break;

  case SwitchCharacter:
    _charSwitch.Update();
    break;  
  }
}

void BattleMenu::Draw(sf::RenderTarget& renderTarget)
{
  switch(_menuState)
  {
  case ActionSelect:
    BlackDragonEngine::Menu::Draw(renderTarget);
    break;

  case TargetSelection:
    _targetSelectMenu.Draw(renderTarget);
    break;

   case SpellSelect:
    BlackDragonEngine::Menu::Draw(renderTarget);
    _spellSelectMenu.Draw(renderTarget);
    break;

  case SwitchCharacter:
    _charSwitch.Draw(renderTarget);
    break;
  }
}

void BattleMenu::SelectMenuItem()
{
  sf::String const& selectedItem = SelectedItem();
  if(selectedItem == Attack)
  {
    _menuState = TargetSelection;
    _targetSelectMenu.ResetMenu();
    _targetInfo.Spell = _currentAttacker->GetSpells()[0];
  }

  if(selectedItem == Spell)
  {
    _menuState = SpellSelect;
    _spellSelectMenu.ResetMenu(_currentAttacker);
  }

  if(selectedItem == Defend)
  {
    _targetInfo.Spell = _currentAttacker->GetSpells()[1];
    _targetInfo.Target = _currentAttacker;
    _battle.SetTargetInfo(_targetInfo);
    _battle.SetBattleState(Battle::Action);
  }

  if(selectedItem == Switch)
  {
    _menuState = SwitchCharacter;
    _charSwitch.ResetMenu();
  }

  if(selectedItem == Convince)
  {
    _battle.SetBattleState(Battle::Idle);
    GameStateManager::SetState(GameStates::Ingame);
  }
}

void BattleMenu::SetCurrentAttacker(Character* currentAttacker)
{
  _currentAttacker = currentAttacker;
}

Character* BattleMenu::GetCurrentAttacker()
{
  return _currentAttacker;
}

void BattleMenu::SetTarget(Character* target)
{
  _targetInfo.Target = target;
  _battle.SetBattleState(Battle::Action);
  _battle.SetTargetInfo(_targetInfo);
}

void BattleMenu::SetSpell(ISpell* spell)
{
  _targetInfo.Spell = spell;
  TargetInfo::TargetType targetType = spell->GetTargetType();
  if(targetType == TargetInfo::Single || targetType == TargetInfo::Decaying)
  {
    _menuState = TargetSelection;
    _targetSelectMenu.ResetMenu();
  }
  else
  {    
    _battle.SetTargetInfo(_targetInfo);
    _battle.SetBattleState(Battle::Action);
  }
}

BattleMenu::BMenuState BattleMenu::GetMenuState()
{
  return _menuState;
}

void BattleMenu::SetMenuState(BattleMenu::BMenuState newState)
{
  _menuState = newState;
}

void BattleMenu::ResetMenu()
{
  BlackDragonEngine::Menu::ResetMenu();
  _menuState = ActionSelect;
}

void BattleMenu::WorkFinished()
{
  _targetInfo.Spell = Spells::GetSpell("Switch");
  _battle.SetBattleState(Battle::Action);
  _battle.SetTargetInfo(_targetInfo);
}

void BattleMenu::WorkCancelled()
{
  ResetMenu();
}

}
