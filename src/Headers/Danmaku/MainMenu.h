#pragma once
#include "BlackDragonEngine/Menu.h"
#include "BlackDragonEngine/Game.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"

namespace Danmaku
{
class MainMenu : public BlackDragonEngine::Menu
{
public:
  MainMenu();
  void Update();
  void SelectMenuItem();
private:
  sf::String const NewGame;
  sf::String const Resume;
  sf::String const Quit;
};
}
