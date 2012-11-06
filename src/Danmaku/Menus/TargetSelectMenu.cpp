#include "Danmaku/TargetSelectMenu.h"
#include "Danmaku/Battle.h"
#include "Danmaku/Party.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/MenuLabel.h"
#include "BlackDragonEngine/MenuItem.h"

namespace Danmaku
{

TargetSelectMenu::TargetSelectMenu(Battle& battle, BattleMenu& battleMenu)
  : Enemies("----------Enemies----------"),
    Party("------------Party------------"), _battle(battle),
    _battleMenu(battleMenu)
{
  using namespace BlackDragonEngine;
  AddMenuLabel(new MenuLabel(Enemies, FontName));
  AddMenuLabel(new MenuLabel(Party, FontName));
  MenuLabels[0]->SetPosition(25.f, 370.f);
  MenuLabels[1]->SetPosition(25.f, 425.f);
  MenuLabels[0]->SetColor(sf::Color::White);
  MenuLabels[1]->SetColor(sf::Color::White);
  MenuLabels[0]->SetFontSize(13u);
  MenuLabels[1]->SetFontSize(13u);
}

void TargetSelectMenu::SelectMenuItem()
{
  sf::String const& selectedItem = SelectedItem();
  _battleMenu.SetTarget(_nameCharMap[selectedItem.toAnsiString()]);
}

void TargetSelectMenu::ResetMenu()
{
  using namespace BlackDragonEngine;
  ClearMenuItems();
  _nameCharMap.clear();
  Battle::CharVec& enemies = _battle.GetEnemies();
  Party::FrontRow& players = _battle.GetFrontRow();

  int ic(0);
  for(size_t i = 0; i < 2u; ++i)
  {
    if(enemies[i].IsDead())
      continue;
    MenuItem* newItem = new MenuItem(enemies[i].GetDisplayName());
    newItem->SetFontSize(13u);
    AddMenuItem(newItem);
    _nameCharMap[enemies[i].GetDisplayName().toAnsiString()] = &enemies[i];

    if(i == 0)
      MenuItems[ic++]->SetPosition(12.f, 388.f);
    else
      MenuItems[ic++]->SetPosition(12.f, 407.f);
  }

  for(size_t i = 0; i < 2u; ++i)
  {
    if(players[i].IsDead())
      continue;
    MenuItem* newItem = new MenuItem(players[i].GetDisplayName());
    newItem->SetFontSize(13u);
    AddMenuItem(newItem);
    _nameCharMap[players[i].GetDisplayName().toAnsiString()] = &players[i];

    if(i == 0)
      MenuItems[ic++]->SetPosition(12.f, 440.f);
    else
      MenuItems[ic++]->SetPosition(12.f, 459.f);
  }

  for(size_t i = 2; i < enemies.size(); ++i)
  {
    if(enemies[i].IsDead())
      continue;
    MenuItem* newItem = new MenuItem(enemies[i].GetDisplayName());
    newItem->SetFontSize(13u);
    AddMenuItem(newItem);
    _nameCharMap[enemies[i].GetDisplayName().toAnsiString()] = &enemies[i];

    if(i == 2u)
      MenuItems[ic++]->SetPosition(113.f, 388.f);
    else
      MenuItems[ic++]->SetPosition(113.f, 407.f);
  }

  for(size_t i = 2; i < players.size(); ++i)
  {
    if(players[i].IsDead())
      continue;
    MenuItem* newItem = new MenuItem(players[i].GetDisplayName());
    newItem->SetFontSize(13u);
    AddMenuItem(newItem);
    _nameCharMap[players[i].GetDisplayName().toAnsiString()] = &players[i];

    if(i == 2)
      MenuItems[ic++]->SetPosition(113.f, 440.f);
    else
      MenuItems[ic++]->SetPosition(113.f, 459.f);
  }
  MenuItems[0]->SetSelected(true);
}

void TargetSelectMenu::Update()
{
  using namespace BlackDragonEngine;
  Menu::Update();
  if(Input::Cancel(true))
    _battleMenu.SetMenuState(BattleMenu::ActionSelect);
  if(Input::Left(true))
    SelectMenuItemHorizontal(Left);
  if(Input::Right(true))
    SelectMenuItemHorizontal(Right);
}

void TargetSelectMenu::SelectMenuItemHorizontal(Direction direction)
{
  bool phaseTwo(false);
  sf::Vector2f pos;
  int oldSelect(0);
  for(int i = 0; i < (int)MenuItems.size(); ++i)
  {
    if(!MenuItems[i]->IsSelected() && !phaseTwo)
      continue;

    if(phaseTwo && MenuItems[i]->GetPosition().y == pos.y &&
       ((direction == Left && MenuItems[i]->GetPosition().x < pos.x) ||
        (direction == Right && MenuItems[i]->GetPosition().x > pos.x)))
    {
      MenuItems[oldSelect]->SetSelected(false);
      MenuItems[i]->SetSelected(true);
      return;
    }
    if(phaseTwo)
      continue;
    phaseTwo = true;
    pos = MenuItems[i]->GetPosition();
    oldSelect = i;
    i = -1;
  }
}

}
