#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/Input.h"
#include "Danmaku/Ingame.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/MainMenu.h"
#include "BlackDragonEngine/MenuItem.h"

namespace Danmaku
{
MainMenu::MainMenu()
  : NewGame("New Game"), Resume("Resume Game"), Quit("Quit")
{
  using namespace BlackDragonEngine;
  AddMenuItem(new MenuItem(Resume, FontName, false));
  AddMenuItem(new MenuItem(NewGame, FontName, true));
  AddMenuItem(new MenuItem(Quit, FontName, false));
  EnableMouseSelection = false;
  SetPositions();
}
void MainMenu::Update()
{
  using namespace BlackDragonEngine;
  if(Input::Cancel(true))
    Game::Exit();
  Menu::Update();
}
void MainMenu::SelectMenuItem()
{
  using namespace BlackDragonEngine;
  sf::String const& selectedItem = SelectedItem();
  if(selectedItem == Quit)
    Game::Exit();
  else if(selectedItem == NewGame)
  {
    GameStateManager::SetState(GameStates::Ingame);
    Ingame::NewGame();
  }
}

}

