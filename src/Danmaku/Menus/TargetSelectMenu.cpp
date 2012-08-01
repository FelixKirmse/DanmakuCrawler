#include "Danmaku/TargetSelectMenu.h"
#include "Danmaku/Battle.h"
#include "Danmaku/Party.h"
#include "BlackDragonEngine/Input.h"

namespace Danmaku
{

TargetSelectMenu::TargetSelectMenu(Battle& battle, BattleMenu& battleMenu)
  : Enemies("----------Enemies----------"),
    Party("------------Party------------"), _battle(battle),
    _battleMenu(battleMenu)
{
  using namespace BlackDragonEngine;
  MenuLabels.push_back(MenuLabel(Enemies, FontName));
  MenuLabels.push_back(MenuLabel(Party, FontName));
  MenuLabels[0].SetPosition(25.f, 370.f);
  MenuLabels[1].SetPosition(25.f, 425.f);
  MenuLabels[0].SetColor(sf::Color(sf::Color::White));
  MenuLabels[1].SetColor(sf::Color(sf::Color::White));
  MenuLabels[0].SetFontSize(13u);
  MenuLabels[1].SetFontSize(13u);
}

void TargetSelectMenu::SelectMenuItem()
{
  sf::String const& selectedItem = SelectedItem();
  _battleMenu.SetTarget(_nameCharMap[selectedItem.toAnsiString()]);
}

void TargetSelectMenu::ResetMenu()
{
  using namespace BlackDragonEngine;
  MenuItems.clear();
  _nameCharMap.clear();
  Battle::CharVec& enemies = _battle.GetEnemies();
  Party::FrontRow& players = _battle.GetFrontRow();

  for(size_t i = 0; i < 2; ++i)
  {
    MenuItem newItem(enemies[i].GetDisplayName());
    newItem.SetFontSize(13u);
    MenuItems.push_back(newItem);
    _nameCharMap[enemies[i].GetDisplayName().toAnsiString()] = &enemies[i];
  }
  int ic(0);

  MenuItems[ic].SetSelected(true);
  MenuItems[ic++].SetPosition(12.f, 388.f);
  MenuItems[ic++].SetPosition(12.f, 407.f);

  for(size_t i = 0; i < 2; ++i)
  {
    MenuItem newItem(players[i].GetDisplayName());
    newItem.SetFontSize(13u);
    MenuItems.push_back(newItem);
    _nameCharMap[players[i].GetDisplayName().toAnsiString()] = &players[i];
  }

  MenuItems[ic++].SetPosition(12.f, 440.f);
  MenuItems[ic++].SetPosition(12.f, 459.f);

  for(size_t i = 2; i < enemies.size(); ++i)
  {
    MenuItem newItem(enemies[i].GetDisplayName());
    newItem.SetFontSize(13u);
    MenuItems.push_back(newItem);
    _nameCharMap[enemies[i].GetDisplayName().toAnsiString()] = &enemies[i];
  }

  MenuItems[ic++].SetPosition(113.f, 388.f);
  if(enemies.size() == 4)
    MenuItems[ic++].SetPosition(113.f, 407.f);

  for(size_t i = 2; i < players.size(); ++i)
  {
    MenuItem newItem(players[i].GetDisplayName());
    newItem.SetFontSize(13u);
    MenuItems.push_back(newItem);
    _nameCharMap[players[i].GetDisplayName().toAnsiString()] = &players[i];
  }

  MenuItems[ic++].SetPosition(113.f, 440.f);
  MenuItems[ic++].SetPosition(113.f, 459.f);
}

void TargetSelectMenu::Update()
{
  using namespace BlackDragonEngine;
  Menu::Update();
  if(Input::Cancel(true))
    _battleMenu.SetMenuState(BattleMenu::ActionSelect);
  if(Input::Left(true))
    SelectMenuItemHorizontal(-4);
  if(Input::Right(true))
    SelectMenuItemHorizontal(4);
}

void TargetSelectMenu::SelectMenuItemHorizontal(int offset)
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(!MenuItems[i].IsSelected())
      continue;

    MenuItems[i].SetSelected(false);
    MenuItems[(i + offset < 0 ||
               i + offset > MenuItems.size()) ?
          i : i + offset].SetSelected(true);
    break;
  }
}

}
