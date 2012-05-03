#include "Danmaku/Menu.h"
namespace Danmaku
{
Menu::Menu()
  : _mainMenu()
{
  State = MenuStates::Main;
}

bool Menu::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Menu;
}

bool Menu::Update()
{
  switch(State)
  {
  case MenuStates::Main:
    _mainMenu.Update();
    break;
  default:
    break;
  }
  return true;
}

bool Menu::DrawCondition()
{
  return GameStateManager::GetState() == GameStates::Menu;
}

void Menu::Draw(float /*interpolation*/, RenderTarget& renderTarget)
{
  switch(State)
  {
  case MenuStates::Main:
    _mainMenu.Draw(renderTarget);
    break;
  default:
    break;
  }
}

void Menu::SetState(MenuState state)
{
  State = state;
}

MenuState Menu::GetState()
{
  return State;
}

MenuState Menu::State;

}

