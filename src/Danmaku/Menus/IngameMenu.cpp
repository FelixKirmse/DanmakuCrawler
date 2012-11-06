#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/Input.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Menu.h"
#include "Danmaku/IngameMenu.h"
#include "BlackDragonEngine/MenuItem.h"

namespace Danmaku
{
IngameMenu::IngameMenu()
  : Resume("Resume"), BackToMenu("Back to Main Menu")
{
  using namespace BlackDragonEngine;
  AddMenuItem(new MenuItem(Resume, FontName, true));
  AddMenuItem(new MenuItem(BackToMenu, FontName));
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

