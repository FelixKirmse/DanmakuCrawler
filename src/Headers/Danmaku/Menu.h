#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "Danmaku/MainMenu.h"
#include "Danmaku/States.h"


namespace Danmaku
{
using BlackDragonEngine::IDrawableGameState;
using BlackDragonEngine::IUpdateableGameState;
using namespace sf;
using namespace std;
typedef MenuStates::MenuStates MenuState;

class MainMenu;

class Menu : public IDrawableGameState, public IUpdateableGameState
{
public:
  Menu();

  bool UpdateCondition();
  bool Update();

  bool DrawCondition();
  void Draw(float /*interpolation*/, RenderTarget& renderTarget);

  static void SetState(MenuState state);
  static MenuState GetState();
private:
  unique_ptr<MainMenu> _mainMenu;
  static MenuState State;
};
}
