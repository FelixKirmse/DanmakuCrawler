#include "Danmaku/IngameMenu.h"

namespace Danmaku
{
IngameMenu::IngameMenu()
  : Resume("Resume"), BackToMenu("Back to Main Menu")
{
  using namespace BlackDragonEngine;
  MenuItems.push_back(MenuItem(Resume, FontName, true));
  MenuItems.push_back(MenuItem(BackToMenu, FontName));
  SetPositions();
  EnableMouseSelection = false;
}

void IngameMenu::Update()
{
  if(BlackDragonEngine::Input::Cancel(true))
    GameStateManager::SetState(GameStates::Ingame);
  BlackDragonEngine::Menu::Update();
}

void IngameMenu::SelectMenuItem()
{
  using namespace BlackDragonEngine;
  sf::String const& selectedItem = SelectedItem();
  if(selectedItem == Resume)
    GameStateManager::SetState(GameStates::Ingame);
  else if(selectedItem == BackToMenu)
    Danmaku::Menu::SetState(MenuStates::Main);
}
}

