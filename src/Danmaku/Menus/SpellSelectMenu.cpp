#include "Danmaku/SpellSelectMenu.h"
#include "Danmaku/BattleMenu.h"
#include "Danmaku/Character.h"
#include "Danmaku/Spells/ISpell.h"
#include "BlackDragonEngine/Input.h"

namespace Danmaku
{

SpellSelectMenu::SpellSelectMenu(BattleMenu& battleMenu)
  : Description("Description:"), MP(" MP"), DescriptionOrigin(250.f, 205.f),
    OriginY(260.f), SpellOriginX(250.f), MPCostOriginX(615.f), YOffset(15.f),
    _backDrop(sf::Vector2f(390.f, 170.f)), _battleMenu(battleMenu)
{
  ItemOffset.y = YOffset;
  _backDrop.setPosition(240.f, 185.f);
  _backDrop.setFillColor(sf::Color::Black);
  _backDrop.setOutlineColor(sf::Color::White);
}

void SpellSelectMenu::ResetMenu(Character* currentAttacker)
{
  using namespace BlackDragonEngine;
  _currentAttacker = currentAttacker;
  MenuItems.clear();
  MenuLabels.clear();
  _nameSpellMap.clear();
  Character::SpellList& spells = currentAttacker->GetSpells();
  for(size_t i = 2; i < spells.size(); ++i)
  {
    int mpCost = spells[i]->GetMPCost(*currentAttacker);
    bool selectable(_currentAttacker->CurrentMP() + 1.f >= mpCost &&
                    !_currentAttacker->IsSilenced());

    MenuItem newItem(spells[i]->GetName());
    newItem.SetFontSize(13u);
    newItem.SetSelectable(selectable);
    MenuItems.push_back(newItem);

    MenuLabel newLabel(std::to_string(mpCost) + MP, FontName);
    newLabel.SetColor(selectable ? sf::Color::White : sf::Color(128u,128u,128u));
    newLabel.SetFontSize(13u);
    MenuLabels.push_back(newLabel);

    _nameSpellMap[newItem.GetName().toAnsiString()] = spells[i];
  }
  SetPositions(sf::Vector2f(SpellOriginX, OriginY), false, 0);
  SetLabelPositions(sf::Vector2f(MPCostOriginX, OriginY + 10.f), false, 0, true);

  for(auto& item : MenuItems)
  {
    if(!item.IsSelectable())
      continue;
    item.SetSelected(true);
    break;
  }

  AddStandardMenuLabels();
  MenuLabels.back().SetText(spells[2]->GetDescription());
}

void SpellSelectMenu::Update()
{
  using namespace BlackDragonEngine;
  Menu::Update();
  if(Input::Down(true) || Input::Up(true))
    MenuLabels.back().SetText(_nameSpellMap[SelectedItem().toAnsiString()]
                          ->GetDescription());
  if(Input::Cancel(true))
    _battleMenu.SetMenuState(BattleMenu::ActionSelect);
}

void SpellSelectMenu::AddStandardMenuLabels()
{
  using namespace BlackDragonEngine;
  MenuLabels.push_back(MenuLabel(Description, FontName));
  MenuLabels.push_back(MenuLabel("This should never appear.", FontName));
  size_t size = MenuLabels.size();
  MenuLabels[size - 2].SetPosition(250.f, 190.f);
  MenuLabels[size - 1].SetPosition(DescriptionOrigin);
  MenuLabels[size - 2].SetColor(sf::Color::White);
  MenuLabels[size - 1].SetColor(sf::Color::White);
  MenuLabels[size - 2].SetFontSize(13u);
  MenuLabels[size - 1].SetFontSize(13u);
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
  _battleMenu.SetSpell(selectedSpell);
}

}
