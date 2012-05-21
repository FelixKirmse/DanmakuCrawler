#include "Danmaku/MainMenu.h"

namespace Danmaku
{
MainMenu::MainMenu()
  : NewGame("New Game"), Resume("Resume Game"), Quit("Quit")
{
  using namespace BlackDragonEngine;
  MenuItems.push_back(MenuItem(Resume, FontName, false));
  MenuItems.push_back(MenuItem(NewGame, FontName, true));
  MenuItems.push_back(MenuItem(Quit, FontName, false));
  EnableMouseSelection = true;
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

