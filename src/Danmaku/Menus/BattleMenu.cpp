#include "Danmaku/BattleMenu.h"
#include "Danmaku/Battle.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/Character.h"

namespace Danmaku
{

BattleMenu::BattleMenu(Battle& battle)
  : Attack("Attack"), Spell("Spell"), Defend("Defend"), Switch("Switch"),
    Convince("Convince"), _menuState(ActionSelect), _battle(battle),
    _targetSelectMenu(battle, *this)
{
  using namespace BlackDragonEngine;
  MenuItems.push_back(MenuItem(Attack, FontName, true));
  MenuItems.push_back(MenuItem(Spell));
  MenuItems.push_back(MenuItem(Defend));
  MenuItems.push_back(MenuItem(Switch));
  MenuItems.push_back(MenuItem(Convince));
  EnableMouseSelection = false;
  SetPositions(sf::Vector2f(10.f, 408.f), false);
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
    break;

  case SelectCharToSwitch:
    break;

  case SelectCharToSwitchWith:
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
    break;

  case SelectCharToSwitch:
    break;

  case SelectCharToSwitchWith:
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

  if(selectedItem == Defend)
  {
    _targetInfo.Spell = _currentAttacker->GetSpells()[1];
    _targetInfo.Target = _currentAttacker;
    _battle.SetTargetInfo(_targetInfo);
    _battle.SetBattleState(Battle::Consequences);
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

void BattleMenu::SetTarget(Character* target)
{
  _targetInfo.Target = target;
  _battle.SetBattleState(Battle::Consequences);
  _battle.SetTargetInfo(_targetInfo);
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

}
