#include "Danmaku/SpellSelectMenu.h"
#include "Danmaku/BattleMenu.h"
#include "Danmaku/Character.h"
#include "Danmaku/Spells/ISpell.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/MenuItem.h"
#include "BlackDragonEngine/MenuLabel.h"

namespace Danmaku
{

SpellSelectMenu::SpellSelectMenu()
  : SpellSelectMenu(NULL)
{
}


SpellSelectMenu::SpellSelectMenu(BattleMenu* battleMenu)
  : Description("Description:"), MP(" MP"), DescriptionOrigin(250.f, 35.f),
    OriginY(260.f), SpellOriginX(250.f), MPCostOriginX(615.f), YOffset(15.f),
    _backDrop(sf::Vector2f(390.f, 340.f)), _battleMenu(battleMenu)
{
  ItemOffset.y = YOffset;
  _backDrop.setPosition(240.f, 16.f);
  _backDrop.setFillColor(sf::Color::Black);
  _backDrop.setOutlineColor(sf::Color::White);
}

void SpellSelectMenu::ResetMenu(Character* currentAttacker)
{
  using namespace BlackDragonEngine;
  _currentAttacker = currentAttacker;
  ClearMenuItems();
  ClearLabels();
  _nameSpellMap.clear();
  Character::SpellList& spells = currentAttacker->GetSpells();
  for(size_t i = 2; i < spells.size(); ++i)
  {
    int mpCost = spells[i]->GetMPCost(*currentAttacker);
    bool selectable(_currentAttacker->CurrentMP() + 1.f >= mpCost &&
                    !_currentAttacker->IsSilenced());

    MenuItem* newItem = new MenuItem(spells[i]->GetName());
    newItem->SetFontSize(13u);
    newItem->SetSelectable(selectable);
    AddMenuItem(newItem);

    MenuLabel* newLabel = new MenuLabel(std::to_string(mpCost) + MP, FontName);
    newLabel->SetColor(selectable ? sf::Color::White : sf::Color(128u,128u,128u));
    newLabel->SetFontSize(13u);
    AddMenuLabel(newLabel);

    _nameSpellMap[newItem->GetName().toAnsiString()] = spells[i];
  }
  SetPositions(sf::Vector2f(SpellOriginX, OriginY), false, 0);
  SetLabelPositions(sf::Vector2f(MPCostOriginX, OriginY + 10.f), false, 0, true);

  for(MenuItem* item : MenuItems)
  {
    if(!item->IsSelectable())
      continue;
    item->SetSelected(true);
    break;
  }

  AddStandardMenuLabels();
  MenuLabels.back()->SetText(spells[2]->GetDescription());
}

void SpellSelectMenu::SetDescription(sf::String const& description)
{
  MenuLabels.back()->SetText(description);
}

void SpellSelectMenu::Update()
{
  using namespace BlackDragonEngine;
  Menu::Update();
  if(Input::Down(true) || Input::Up(true))
    SetDescription(_nameSpellMap[SelectedItem().toAnsiString()]->GetDescription());
  if(Input::Cancel(true) && _battleMenu != NULL)
    _battleMenu->SetMenuState(BattleMenu::ActionSelect);
}

void SpellSelectMenu::AddStandardMenuLabels()
{
  using namespace BlackDragonEngine;
  AddMenuLabel(new MenuLabel(Description, FontName));
  AddMenuLabel(new MenuLabel("This should never appear.", FontName));
  size_t size = MenuLabels.size();
  MenuLabels[size - 2]->SetPosition(250.f, 20.f);
  MenuLabels[size - 1]->SetPosition(DescriptionOrigin);
  MenuLabels[size - 2]->SetColor(sf::Color::White);
  MenuLabels[size - 1]->SetColor(sf::Color::White);
  MenuLabels[size - 2]->SetFontSize(13u);
  MenuLabels[size - 1]->SetFontSize(13u);
}

void SpellSelectMenu::Draw(sf::RenderTarget& renderTarget)
{
  renderTarget.draw(_backDrop);
  BlackDragonEngine::Menu::Draw(renderTarget);
}

void SpellSelectMenu::SelectMenuItem()
{
  sf::String const& selectedItem = SelectedItem();
  ISpell* selectedSpell = _nameSpellMap[selectedItem.toAnsiString()];  
  if(_battleMenu != NULL)
    _battleMenu->SetSpell(selectedSpell);
}

}
