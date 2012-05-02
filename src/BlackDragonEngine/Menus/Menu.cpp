#include "BlackDragonEngine/Menu.h"

namespace BlackDragonEngine
{

Menu::Menu()
  : FontName("Vera"), EnableMouseSelection(true), ItemOffset(Vector2f(0, 24))
{
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
    MenuItems[i].Update();
}

void Menu::Draw(RenderTarget& renderTarget)
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
    MenuItems[i].Draw(renderTarget);
  for(size_t i = 0; i < MenuLabels.size(); ++i)
    MenuLabels[i].Draw(renderTarget);
}

void Menu::NextMenuItem()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i].IsSelected())
    {
      MenuItems[i].SetSelected(false);
      if(i == MenuItems.size() - 1)
        MenuItems[0].SetSelected(true);
      else
        MenuItems[i + 1].SetSelected(true);
      break;
    }
  }
}

void Menu::PreviousMenuItem()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i].IsSelected())
    {
      MenuItems[i].SetSelected(false);
      if(i == 0)
        MenuItems[MenuItems.size() - 1].SetSelected(true);
      else
        MenuItems[i - 1].SetSelected(true);
      break;
    }
  }
}

void Menu::ResolveMouseSelection()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(Input::MouseInsideRectangle(MenuItems[i].GetWorldRectangle()))
    {
      for(size_t j = 0; j < MenuItems.size(); ++j)
        MenuItems[j].SetSelected(false);
      MenuItems[i].SetSelected(true);
      break;
    }
  }
}

String const& Menu::SelectedItem()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
    if(MenuItems[i].IsSelected())
      return MenuItems[i].GetName();
  return MenuItems[0].GetName();
}

void Menu::SetPositions()
{
  for(int i = 0; i < (int)MenuItems.size(); ++i)
  {
    Vector2f screenCenter = Game::GetScreenCenter();
    FloatRect fontBound = MenuItems[i].GetLocalRectangle();
    Vector2f fontCenter = Vector2f(fontBound.width/2, fontBound.height/2);
    MenuItems[i].SetPosition(screenCenter - fontCenter +
                             Vector2f((i-2)*ItemOffset.x, (i-2)*ItemOffset.y));
  }
}

}

