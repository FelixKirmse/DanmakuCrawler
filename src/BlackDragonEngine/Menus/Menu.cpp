#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Menu.h"
#include "BlackDragonEngine/MenuItem.h"
#include "BlackDragonEngine/MenuLabel.h"

namespace BlackDragonEngine
{

Menu::Menu()
  : FontName("Vera"), EnableMouseSelection(false),
    ItemOffset(sf::Vector2f(0, 24))
{
}

Menu::~Menu()
{
  for(MenuItem* item : MenuItems)
  {
    delete item;
  }

  for(MenuLabel* label : MenuLabels)
  {
    delete label;
  }
}

void Menu::Update()
{
  if(Input::Down(true))
    NextMenuItem();

  if(Input::Up(true))
    PreviousMenuItem();

  if(EnableMouseSelection)
    ResolveMouseSelection();

  if(Input::Action(true) ||
     (EnableMouseSelection && Input::LeftClick(true)))
    SelectMenuItem();

  for(size_t i = 0; i < MenuItems.size(); ++i)
    MenuItems[i]->Update();
}

void Menu::Draw(sf::RenderTarget& renderTarget)
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
    MenuItems[i]->Draw(renderTarget);
  for(size_t i = 0; i < MenuLabels.size(); ++i)
    MenuLabels[i]->Draw(renderTarget);
}

void Menu::NextMenuItem()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i]->IsSelected())
    {
      MenuItems[i]->SetSelected(false);
      int nextItem(i == MenuItems.size() - 1 ? 0 : i + 1);
      MenuItems[nextItem]->SetSelected(true);
      if(!MenuItems[nextItem]->IsSelectable())
        NextMenuItem();
      break;
    }
  }
}

void Menu::PreviousMenuItem()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i]->IsSelected())
    {
      MenuItems[i]->SetSelected(false);
      int lastItem(i == 0 ? MenuItems.size() - 1 : i - 1);
      MenuItems[lastItem]->SetSelected(true);
      if(!MenuItems[lastItem]->IsSelectable())
        PreviousMenuItem();
      break;
    }
  }
}

void Menu::ResolveMouseSelection()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(Input::MouseInsideRectangle(MenuItems[i]->GetWorldRectangle()))
    {
      for(size_t j = 0; j < MenuItems.size(); ++j)
        MenuItems[j]->SetSelected(false);
      MenuItems[i]->SetSelected(true);
      break;
    }
  }
}

sf::String const& Menu::SelectedItem()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
    if(MenuItems[i]->IsSelected())
      return MenuItems[i]->GetName();
  return MenuItems[0]->GetName();
}


void Menu::SetPositions(sf::Vector2f position, bool centered,
                        int offset)
{
  for(int i = 0; i < (int)MenuItems.size(); ++i)
  {
    sf::FloatRect fontBound = MenuItems[i]->GetLocalRectangle();
    sf::Vector2f fontCenter = (centered) ? sf::Vector2f(fontBound.width/2,
                                                        fontBound.height/2) :
                                           sf::Vector2f(0.f, 0.f);
    MenuItems[i]->SetPosition(position - fontCenter +
                              sf::Vector2f((i + offset)*ItemOffset.x,
                                           (i + offset)*ItemOffset.y));
  }
}

void Menu::SetLabelPositions(sf::Vector2f position, bool centered,
                             int offset, bool originBottomRight)
{
  for(int i = 0; i < (int)MenuLabels.size(); ++i)
  {
    sf::FloatRect fontBound = MenuLabels[i]->GetLocalRectangle();
    sf::Vector2f fontCenter = (centered) ? sf::Vector2f(fontBound.width/2,
                                                        fontBound.height/2) :
                                           sf::Vector2f(0.f, 0.f);
    MenuLabels[i]->SetPosition(position - fontCenter -
                               (originBottomRight ?
                                  sf::Vector2f(MenuLabels[i]->GetLocalRectangle()
                                               .width, MenuLabels[i]
                                               ->GetLocalRectangle().height) :
                                  sf::Vector2f(0.f, 0.f)) +
                               sf::Vector2f((i + offset)*ItemOffset.x,
                                            (i + offset)*ItemOffset.y));
  }
}

void Menu::ResetMenu()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
    if(MenuItems[i]->IsSelected())
      MenuItems[i]->SetSelected(false);
  MenuItems[0]->SetSelected(true);
}

void Menu::AddMenuItem(MenuItem* item)
{
  MenuItems.push_back(item);
}

void Menu::AddMenuLabel(MenuLabel* label)
{
  MenuLabels.push_back(label);
}

void Menu::ClearMenuItems()
{
  for(MenuItem* item : MenuItems)
  {
    delete item;
  }
  MenuItems.clear();
}

void Menu::ClearLabels()
{
  for(MenuLabel* label : MenuLabels)
  {
    delete label;
  }
  MenuLabels.clear();
}

}

