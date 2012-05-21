#pragma once
#include "BlackDragonEngine/Menu.h"
#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/Input.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/Menu.h"

namespace Danmaku
{
class IngameMenu : public BlackDragonEngine::Menu
{
public:
  IngameMenu();
  void Update();
  void SelectMenuItem();
private:
  sf::String const Resume;
  sf::String const BackToMenu;
};
}
