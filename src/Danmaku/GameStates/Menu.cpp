#include "Danmaku/Menu.h"
namespace Danmaku
{
Menu::Menu()
  : _mainMenu(new MainMenu()), _ingameMenu(new IngameMenu())
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
    _mainMenu->Update();
    break;
  case MenuStates::Ingame:
    _ingameMenu->Update();
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

void Menu::Draw(float /*interpolation*/, sf::RenderTarget& renderTarget)
{
  switch(State)
  {
  case MenuStates::Main:
    _mainMenu->Draw(renderTarget);
    break;
  case MenuStates::Ingame:
    _ingameMenu->Draw(renderTarget);
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

