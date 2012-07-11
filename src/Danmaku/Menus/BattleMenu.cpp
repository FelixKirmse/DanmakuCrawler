#include "Danmaku/BattleMenu.h"
#include "Danmaku/Battle.h"

namespace Danmaku
{

BattleMenu::BattleMenu(Battle& battle)
  : Attack("Attack"), Spell("Spell"), Defend("Defend"), Switch("Switch"),
    Convince("Convince"), _menuState(ActionSelect), _battle(battle)
{
  using namespace BlackDragonEngine;
  MenuItems.push_back(MenuItem(Attack, FontName, true));
  MenuItems.push_back(MenuItem(Spell));
  MenuItems.push_back(MenuItem(Defend));
  MenuItems.push_back(MenuItem(Switch));
  MenuItems.push_back(MenuItem(Convince));
  EnableMouseSelection = false;
  SetPositions(sf::Vector2f(10.f, 400.f), false);
}

void BattleMenu::Update()
{
  switch(_menuState)
  {
  case ActionSelect:
    BlackDragonEngine::Menu::Update();
    break;

  case TargetSelection:
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
}

}
