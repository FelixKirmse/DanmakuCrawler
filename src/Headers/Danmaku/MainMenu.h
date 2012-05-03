#pragma once
#include "BlackDragonEngine/Menu.h"
#include "BlackDragonEngine/Game.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"

namespace Danmaku
{
using namespace BlackDragonEngine;
using namespace sf;

class MainMenu : public BlackDragonEngine::Menu
{
public:
  MainMenu();
  void Update();
  void SelectMenuItem();
private:
  String const NewGame;
  String const Resume;
  String const Quit;
};
}
